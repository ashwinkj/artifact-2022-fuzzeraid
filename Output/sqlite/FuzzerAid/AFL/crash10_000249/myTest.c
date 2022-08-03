#include "src/he_select.h"
int withExpand(Walker *pWalker, struct SrcList_item *pFrom) {
  Parse *pParse = pWalker->pParse;
  struct Cte *pCte;
  if (pCte) {
    ExprList *pEList;
    if (pCte->pCols) {
      if (pEList->nExpr != pCte->pCols->nExpr) {
      }
    }
  }
}
int sqlite3WalkSelect(Walker *pWalker, Select *p) {
  int i, j, k;
  SrcList *pTabList;
  int *pFrom;
  for (i = 0, pFrom = pTabList->a; i < pTabList->nSrc; i++, pFrom++) {
    if (withExpand(pWalker, pFrom))
      ;
  }
}
void sqlite3SelectExpand(Parse *pParse, Select *pSelect) {
  Walker w;
  sqlite3WalkSelect(&w, pSelect);
}
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  sqlite3SelectExpand(pParse, p);
}
int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  int iEnd;
  sqlite3SelectPrep(pParse, p, 0);
}
int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i, tokenType;
  void *pEngine;
  sqlite3 *db = pParse->db;
  i = 0;
  pEngine = sqlite3ParserAlloc((void *(*)(size_t))sqlite3Malloc);
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
}
int sqlite3Prepare(sqlite3 *db, const char *zSql, int nBytes, int saveSqlFlag,
                   Vdbe *pReprepare, sqlite3_stmt **ppStmt,
                   const char **pzTail) {
  Parse *pParse;
  char *zErrMsg = 0;
  pParse = sqlite3StackAllocZero(db, sizeof *pParse);
  pParse->db = db;
  if (nBytes >= 0 && nBytes == 0 || zSql[nBytes - 1] != 0) {
  } else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
  }
}
int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
}
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
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
    if (z[0] != '-')
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
}
