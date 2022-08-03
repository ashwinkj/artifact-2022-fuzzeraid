#include "src/he_expr.h"
void sqlite3ExprListDelete(sqlite3 *db, ExprList *pList) {
  int i;
  struct ExprList_item *pItem;
  if (pList == 0)
    return;
  for (pItem = pList->a, i = 0; i < pList->nExpr; i++, pItem++) {
    sqlite3ExprDelete(db, pItem->pExpr);
  }
}
void clearSelect(sqlite3 *db, Select *p) {
  sqlite3ExprListDelete(db, p->pEList);
  sqlite3SrcListDelete(db, p->pSrc);
  sqlite3WithDelete(db, p->pWith);
}
void sqlite3SelectDelete(sqlite3 *db, Select *p) {
  if (p) {
    clearSelect(db, p);
    sqlite3DbFree(db, p);
  }
}
void sqlite3WithDelete(sqlite3 *db, With *pWith) {
  if (pWith) {
    int i;
    for (i = 0; i < pWith->nCte; i++) {
      struct Cte *pCte = &pWith->a[i];
      sqlite3SelectDelete(db, pCte->pSelect);
    }
  }
}
int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int nErr = 0, i, tokenType, lastTokenParsed = -1;
  void *pEngine;
  sqlite3 *db = pParse->db;
  i = 0;
  pEngine = sqlite3ParserAlloc((void *(*)(size_t))sqlite3Malloc);
  db->lookaside.bEnabled = 1;
  while (!db->mallocFailed && zSql[i] != 0) {
    pParse->sLastToken.z = &zSql[i];
    pParse->sLastToken.n =
        sqlite3GetToken((unsigned char *)&zSql[i], &tokenType);
    i += pParse->sLastToken.n;
    switch (tokenType) {
    case TK_SPACE: {
      break;
    }
    default: {
      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
    }
    }
  }
  if (zSql[i] == 0 && nErr == 0 && pParse->rc == SQLITE_OK) {
    if (lastTokenParsed != TK_SEMI) {
      sqlite3Parser(pEngine, TK_SEMI, pParse->sLastToken, pParse);
      pParse->zTail = &zSql[i];
    }
  }
}
int sqlite3Prepare(sqlite3 *db, const char *zSql, int nBytes, int saveSqlFlag,
                   Vdbe *pReprepare, sqlite3_stmt **ppStmt,
                   const char **pzTail) {
  Parse *pParse;
  char *zErrMsg = 0;
  int rc = SQLITE_OK;
  pParse = sqlite3StackAllocZero(db, sizeof *pParse);
  pParse->db = db;
  if (nBytes >= 0 && nBytes == 0 || zSql[nBytes - 1] != 0)
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
  }
  if (pzTail) {
    *pzTail = pParse->zTail;
  }
  return rc;
}
int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  *ppStmt = 0;
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
  return rc;
}
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
  return rc;
}
#include "src/he_shell.h"
int main(int argc, char **argv) {
  struct callback_data data;
  const char *zInitFile = 0;
  int i, rc = 0;
  main_init(&data);
  for (i = 1; i < argc; i++) {
    char *z;
    z = argv[i];
    if (strcmp(z, "-separator") == 0 || strcmp(z, "-nullvalue") == 0 ||
        strcmp(z, "-cmd") == 0)
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
}
