#include "src/he_expr.h"
int sqlite3ExprIsInteger(Expr *p, int *pValue) {
  assert(p->op != TK_INTEGER || (p->flags & EP_IntValue) != 0 ||
         sqlite3GetInt32(p->u.zToken, &rc) == 0);
  if (p->flags & EP_IntValue) {
  }
  switch (p->op) {
  case TK_UPLUS:;
  case TK_UMINUS: {
    int v;
    if (sqlite3ExprIsInteger(p->pLeft, &v))
      ;
  } break;
  }
}
int exprAlwaysFalse(Expr *p) {
  int v = 0;
  if (ExprHasProperty(p, EP_FromJoin))
    return 0;
  if (!sqlite3ExprIsInteger(p, &v))
    return 0;
}
Expr *sqlite3ExprAnd(sqlite3 *db, Expr *pLeft, Expr *pRight) {
  if (pLeft == 0)
    ;
  else if (exprAlwaysFalse(pLeft) || exprAlwaysFalse(pRight))
    ;
}
Expr *sqlite3PExpr(Parse *pParse, int op, Expr *pLeft, Expr *pRight,
                   const Token *pToken) {
  Expr *p;
  if (op == TK_AND && pLeft && pRight) {
    p = sqlite3ExprAnd(pParse->db, pLeft, pRight);
  } else {
    p = sqlite3ExprAlloc(pParse->db, op, pToken, 1);
  }
  return p;
}

int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i;
  void *pEngine;
  int tokenType;
  sqlite3 *db = pParse->db;
  int mxSqlLen;
  if (db->nVdbeActive == 0)
    ;
  i = 0;
  pEngine = sqlite3ParserAlloc((void *(*)(size_t))sqlite3Malloc);
  if (pEngine == 0)
    ;
  while (!db->mallocFailed && zSql[i] != 0) {
    pParse->sLastToken.z = &zSql[i];
    pParse->sLastToken.n =
        sqlite3GetToken((unsigned char *)&zSql[i], &tokenType);
    i += pParse->sLastToken.n;
    if (i > mxSqlLen)
      ;
    switch (tokenType) {
    case TK_SPACE: {
      if (db->u1.isInterrupted)
        ;
      break;
    }
    case TK_SEMI:;
    default: {
      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
    }
    }
  }
}

int sqlite3Prepare(sqlite3 *db, const char *zSql, int nBytes, int saveSqlFlag,
                   Vdbe *pReprepare, sqlite3_stmt **ppStmt,
                   const char **pzTail) {
  Parse *pParse;
  char *zErrMsg = 0;
  int rc = SQLITE_OK;
  int i;
  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
  if (pParse == 0)
    ;
  for (i = 0; i < db->nDb; i++)
    ;
  pParse->db = db;
  if (nBytes >= 0 && (nBytes == 0 || zSql[nBytes - 1] != 0))
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
  }
  if (db->mallocFailed)
    ;
  if (rc == SQLITE_OK && pParse->pVdbe && pParse->explain)
    ;
  while (pParse->pTriggerPrg)
    ;
}
#include "src/he_btree.h"

int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
  if (rc == SQLITE_SCHEMA)
    ;
}

int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
#if defined(__APPLE__) && !defined(SQLITE_WITHOUT_ZONEMALLOC)
#endif
}
#include "src/he_shell.h"
int main(int argc, char **argv) {
  char *zErrMsg = 0;
  struct callback_data data;
  const char *zInitFile = 0;
  char *zFirstCmd = 0;
  int i;
  int rc = 0;
  int warnInmemoryDb = 0;
  main_init(&data);
  for (i = 1; i < argc; i++) {
    char *z;
    z = argv[i];
    if (z[0] != '-')
      ;
    if (z[1] == '-')
      z++;
    if (strcmp(z, "-separator") == 0 || strcmp(z, "-nullvalue") == 0 ||
        strcmp(z, "-cmd") == 0)
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    } else if (strcmp(z, "-batch") == 0)
      ;
  }
  rc = process_sqliterc(&data, zInitFile);
  if (zFirstCmd)
    ;
}
