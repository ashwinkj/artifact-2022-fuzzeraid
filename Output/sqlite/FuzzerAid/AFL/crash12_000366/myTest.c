#include "src/he_expr.h"
void sqlite3ExprDelete(sqlite3 *db, Expr *p) {
  if (p == 0)
    return;
  if (!ExprHasProperty(p, EP_TokenOnly)) {
    sqlite3ExprDelete(db, p->pLeft);
  }
}
void resolveAlias(Parse *pParse, ExprList *pEList, int iCol, Expr *pExpr,
                  const char *zType, int nSubquery) {
  Expr *pOrig;
  Expr *pDup;
  sqlite3 *db;
  if (pOrig->op != TK_COLUMN && zType[0] != 'G') {
    pDup = sqlite3ExprAddCollateString(pParse, pDup, pExpr->u.zToken);
  }
  sqlite3ExprDelete(db, pExpr);
}

Expr *sqlite3ExprAlloc(sqlite3 *db, int op, const Token *pToken, int dequote) {
  Expr *pNew;
  int nExtra = 0;
  int iValue = 0;
  if (pToken) {
    if (op != TK_INTEGER || pToken->z == 0 ||
        sqlite3GetInt32(pToken->z, &iValue) == 0) {
      nExtra = pToken->n + 1;
    }
  }
  pNew = sqlite3DbMallocZero(db, sizeof(Expr) + nExtra);
  if (pNew) {
    if (pToken) {
      if (nExtra == 0)
        ;
      else {
        int c;
        pNew->u.zToken = (char *)&pNew[1];
        memcpy(pNew->u.zToken, pToken->z, pToken->n);
        if (dequote && nExtra >= 3 &&
            ((c = pToken->z[0]) == '\'' || c == '"' || c == '[' || c == '`')) {
          sqlite3Dequote(pNew->u.zToken);
        }
      }
    }
  }
  return pNew;
}
int sqlite3ResolveOrderGroupBy(Parse *pParse, Select *pSelect,
                               ExprList *pOrderBy, const char *zType) {
  int i;
  sqlite3 *db = pParse->db;
  ExprList *pEList;
  struct ExprList_item *pItem;
  for (i = 0, pItem = pOrderBy->a; i < pOrderBy->nExpr; i++, pItem++) {
    if (pItem->u.x.iOrderByCol) {
      resolveAlias(pParse, pEList, pItem->u.x.iOrderByCol - 1, pItem->pExpr,
                   zType, 0);
    }
  }
}
int resolveOrderGroupBy(NameContext *pNC, Select *pSelect, ExprList *pOrderBy,
                        const char *zType) {
  int i, j;
  int iCol;
  struct ExprList_item *pItem;
  Parse *pParse;
  int nResult;
  if (pOrderBy == 0)
    return 0;
  pParse = pNC->pParse;
  for (i = 0, pItem = pOrderBy->a; i < pOrderBy->nExpr; i++, pItem++) {
    Expr *pE = pItem->pExpr;
    Expr *pE2 = sqlite3ExprSkipCollate(pE);
    if (sqlite3ExprIsInteger(pE2, &iCol)) {
      pItem->u.x.iOrderByCol = (u16)iCol;
    }
  }
  return sqlite3ResolveOrderGroupBy(pParse, pSelect, pOrderBy, zType);
}
int sqlite3ExprIsInteger(Expr *p, int *pValue) {
}

int resolveSelectStep(Walker *pWalker, Select *p) {
  NameContext sNC;
  int isCompound;
  ExprList *pEList;
  int i;
  ExprList *pGroupBy;
  while (p) {
    if (sqlite3ResolveExprNames(&sNC, p->pLimit) ||
        sqlite3ResolveExprNames(&sNC, p->pOffset)) {
      struct SrcList_item *pItem = &p->pSrc->a[i];
    }
    pEList = p->pEList;
    for (i = 0; i < pEList->nExpr; i++) {
      Expr *pX = pEList->a[i].pExpr;
      if (sqlite3ResolveExprNames(&sNC, pX))
        ;
    }
    if (!isCompound && resolveOrderGroupBy(&sNC, p, p->pOrderBy, "ORDER")) {
      struct ExprList_item *pItem;
    }
    p = p->pPrior;
  }
}
int sqlite3ResolveExprNames(NameContext *pNC, Expr *pExpr) {
  return 0;
  switch (pExpr->op)
    ;
}
int sqlite3WalkSelect(Walker *pWalker, Select *p) {
  int rc;
  if (p == 0 ||
      (pWalker->xSelectCallback == 0 && pWalker->xSelectCallback2 == 0))
    ;
  while (p) {
    if (pWalker->xSelectCallback) {
      rc = pWalker->xSelectCallback(pWalker, p);
    }
    p = p->pPrior;
  }
}
void sqlite3ResolveSelectNames(Parse *pParse, Select *p,
                               NameContext *pOuterNC) {
  Walker w;
  memset(&w, 0, sizeof(w));
  w.xSelectCallback = resolveSelectStep;
  sqlite3WalkSelect(&w, p);
}
#include "src/he_select.h"
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  sqlite3SelectExpand(pParse, p);
  sqlite3ResolveSelectNames(pParse, p, pOuterNC);
}
void sqlite3SelectExpand(Parse *pParse, Select *pSelect) {
  Walker w;
  w.pParse = pParse;
  w.xSelectCallback = selectExpander;
  sqlite3WalkSelect(&w, pSelect);
}
int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  int i, j;
  WhereInfo *pWInfo;
  Vdbe *v;
  int isAgg;
  ExprList *pEList;
  SrcList *pTabList;
  Expr *pWhere;
  ExprList *pGroupBy;
  Expr *pHaving;
  DistinctCtx sDistinct;
  SortCtx sSort;
  AggInfo sAggInfo;
  int iEnd;
  sqlite3 *db;
  int iRestoreSelectId = pParse->iSelectId;
  sqlite3SelectPrep(pParse, p, 0);
  memset(&sSort, 0, sizeof(sSort));
  if (pParse->nErr || db->mallocFailed) {
    struct SrcList_item *pItem = &pTabList->a[i];
    int isAggSub;
    if (pItem->addrFillSub) {
      int topAddr;
      int onceAddr = 0;
    }
    int iAMem;
    int iBMem;
    int iUseFlag;
    int iAbortFlag;
    int groupBySort;
    int addrEnd;
    int orderByGrp = 0;
    if (pGroupBy) {
      pWInfo = sqlite3WhereBegin(pParse, pTabList, pWhere, pGroupBy, 0,
                                 WHERE_GROUPBY | (WHERE_SORTBYGROUP), 0);
      if (sqlite3WhereIsOrdered(pWInfo) == pGroupBy->nExpr) {
        int regBase;
        explainTempTable(pParse,
                         (sDistinct.isTnct && (p->selFlags & SF_Distinct) == 0)
                             ? "DISTINCT"
                             : "GROUP BY");
        for (i = 0; i < sAggInfo.nColumn; i++) {
          struct AggInfo_col *pCol = &sAggInfo.aCol[i];
          if (pCol->iSorterColumn >= j) {
            int r1 = j + regBase;
          }
        }
        ExprList *pMinMax = 0;
      }
    }
  }
}

Select *sqlite3SelectNew(Parse *pParse, ExprList *pEList, SrcList *pSrc,
                         Expr *pWhere, ExprList *pGroupBy, Expr *pHaving,
                         ExprList *pOrderBy, u16 selFlags, Expr *pLimit,
                         Expr *pOffset) {
  Select *pNew;
  sqlite3 *db = pParse->db;
  pNew = sqlite3DbMallocZero(db, sizeof(*pNew));
  pNew->pEList = pEList;
  pNew->pOrderBy = pOrderBy;
  return pNew;
}

int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i;
  void *pEngine;
  int tokenType;
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
int sqlite3MallocSize(void *p) {
}
int sqlite3MemSize(void *pPrior) {
  sqlite3_int64 *p;
  p--;
  return (int)p[0];
}
#include "src/he_mem1.h"
void *sqlite3MemMalloc(int nByte) {
  sqlite3_int64 *p;
  p = SQLITE_MALLOC(nByte + 8);
  if (p) {
    p[0] = nByte;
    p++;
  }
  return (void *)p;
}
int sqlite3Prepare(sqlite3 *db, const char *zSql, int nBytes, int saveSqlFlag,
                   Vdbe *pReprepare, sqlite3_stmt **ppStmt,
                   const char **pzTail) {
  Parse *pParse;
  char *zErrMsg = 0;
  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
  if (pParse == 0)
    ;
  pParse->db = db;
  if (nBytes >= 0 && (nBytes == 0 || zSql[nBytes - 1] != 0))
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
  }
}
int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  if (!sqlite3SafetyCheckOk(db))
    ;
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
}
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
}
void sqlite3MemFree(void *pPrior) {
}
#include "src/he_shell.h"
int main(int argc, char **argv) {
  char *zErrMsg = 0;
  struct callback_data data;
  const char *zInitFile = 0;
  char *zFirstCmd = 0;
  int i;
  int rc = 0;
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
  for (i = 1; i < argc; i++)
    ;
}
