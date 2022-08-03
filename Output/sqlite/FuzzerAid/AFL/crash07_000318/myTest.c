#include "src/he_resolve.h"
int sqlite3MatchSpanName(const char *zSpan, const char *zCol, const char *zTab,
                         const char *zDb) {
  int n;
  for (n = 0; ALWAYS(zSpan[n]) && zSpan[n] != '.'; n++) {
  }
}
#include "src/he_select.h"
int selectExpander(Walker *pWalker, Select *p) {
  Parse *pParse = pWalker->pParse;
  int i, j, k;
  SrcList *pTabList;
  ExprList *pEList;
  struct SrcList_item *pFrom;
  sqlite3 *db = pParse->db;
  Expr *pE, *pRight, *pExpr;
  pTabList = p->pSrc;
  pEList = p->pEList;
  for (i = 0, pFrom = pTabList->a; i < pTabList->nSrc; i++, pFrom++) {
    Table *pTab;
    if (pFrom->zName == 0) {
      Select *pSel = pFrom->pSelect;
      pFrom->pTab = pTab = sqlite3DbMallocZero(db, sizeof(Table));
      selectColumnsFromExprList(pParse, pSel->pEList, &pTab->nCol, &pTab->aCol);
    }
    struct ExprList_item *a = pEList->a;
    for (k = 0; k < pEList->nExpr; k++) {
      pE = a[k].pExpr;
      pRight = pE->pRight;
      if (pE->op != TK_ALL && pE->op != TK_DOT || pRight->op != TK_ALL)
        ;
      else {
        char *zTName = 0;
        if (pE->op == TK_DOT) {
          zTName = pE->pLeft->u.zToken;
          Select *pSub = pFrom->pSelect;
          for (j = 0; j < pTab->nCol; j++) {
            if (zTName && pSub &&
                sqlite3MatchSpanName(pSub->pEList->a[j].zSpan, 0, zTName, 0) ==
                    0)
              ;
          }
        }
      }
    }
  }
}
int sqlite3Strlen30(const char *z) {
}
void *sqlite3DbMallocRaw(sqlite3 *db, int n) {
  void *p;
  if (db) {
    LookasideSlot *pBuf;
    if (db->lookaside.bEnabled) {
      if (n > db->lookaside.sz) {
        return (void *)pBuf;
      }
    }
  }
  p = sqlite3Malloc(n);
  return p;
}
int sqlite3WalkSelect(Walker *pWalker, Select *p) {
  int rc;
  while (p) {
    if (pWalker->xSelectCallback) {
      rc = pWalker->xSelectCallback(pWalker, p);
      break;
    }
  }
}
int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  Parse *pParse;
  char *zErrMsg = 0;
  pParse->db = db;
  if (nBytes >= 0 && nBytes == 0 || zSql[nBytes - 1] != 0)
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
  }
}
void sqlite3Error(sqlite3 *db, int err_code, const char *zFormat, ...) {
}
int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i, tokenType;
  void *pEngine;
  sqlite3 *db = pParse->db;
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
void *sqlite3Malloc(int n) {
  void *p;
  if (n <= 0 || n >= 0x7fffff00)
    ;
  else {
    p = sqlite3GlobalConfig.m.xMalloc(n);
  }
  return p;
}
void *sqlite3HashInsert(Hash *pH, const char *pKey, int nKey, void *data) {
}
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
}
int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  ExprList *pGroupBy;
  sqlite3SelectPrep(pParse, p, 0);
}
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  sqlite3SelectExpand(pParse, p);
}
void sqlite3SelectExpand(Parse *pParse, Select *pSelect) {
  Walker w;
  w.xSelectCallback = selectExpander;
  sqlite3WalkSelect(&w, pSelect);
}
#include "src/he_shell.h"
int main(int argc, char **argv) {
  struct callback_data data;
  const char *zInitFile = 0;
  int i;
  int rc = 0;
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
