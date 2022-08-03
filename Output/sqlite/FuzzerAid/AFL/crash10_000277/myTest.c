#include "src/he_select.h"
int withExpand(Walker *pWalker, struct SrcList_item *pFrom) {
  Parse *pParse = pWalker->pParse;
  sqlite3 *db = pParse->db;
  struct Cte *pCte;
  With *pWith;
  if (pCte) {
    Table *pTab;
    ExprList *pEList;
    if (pCte->pCols) {
      if (pEList->nExpr != pCte->pCols->nExpr) {
      }
    }
  }
}
int sqlite3WalkSelect(Walker *pWalker, Select *p) {
  int rc;
  while (p) {
    if (pWalker->xSelectCallback) {
      rc = pWalker->xSelectCallback(pWalker, p);
    }
  }
}
int selectExpander(Walker *pWalker, Select *p) {
  Parse *pParse = pWalker->pParse;
  int i, j, k;
  SrcList *pTabList;
  ExprList *pEList;
  struct SrcList_item *pFrom;
  sqlite3 *db = pParse->db;
  Expr *pE, *pRight, *pExpr;
  u16 selFlags = p->selFlags;
  pTabList = p->pSrc;
  for (i = 0, pFrom = pTabList->a; i < pTabList->nSrc; i++, pFrom++) {
    Table *pTab;
    if (withExpand(pWalker, pFrom))
      ;
    struct ExprList_item *a = pEList->a;
    ExprList *pNew = 0;
    int flags = pParse->db->flags;
    int longNames =
        flags & SQLITE_FullColNames != 0 && (flags & SQLITE_ShortColNames) == 0;
    for (k = 0; k < pEList->nExpr; k++) {
      if (pE->op != TK_ALL && pE->op != TK_DOT || pRight->op != TK_ALL) {
        int tableSeen = 0;
        char *zTName = 0;
        if (pE->op == TK_DOT) {
          Table *pTab = pFrom->pTab;
          Select *pSub = pFrom->pSelect;
          char *zTabName = pFrom->zAlias;
          const char *zSchemaName = 0;
          int iDb;
          if (pSub == 0 || pSub->selFlags & SF_NestedFrom == 0) {
            zSchemaName = iDb >= 0 ? db->aDb[iDb].zName : "*";
            char *zName = pTab->aCol[j].zName;
            char *zColname;
            char *zToFree;
            Token sColname;
            sqlite3ExprListSetName(pParse, pNew, &sColname, 0);
            if (pNew && p->selFlags & SF_NestedFrom != 0) {
              struct ExprList_item *pX = &pNew->a[pNew->nExpr - 1];
            }
          }
        }
      }
    }
  }
}
void sqlite3SelectExpand(Parse *pParse, Select *pSelect) {
  Walker w;
  w.xSelectCallback = selectExpander;
  sqlite3WalkSelect(&w, pSelect);
}
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  sqlite3SelectExpand(pParse, p);
}
int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  int i, j, isAgg;
  WhereInfo *pWInfo;
  Vdbe *v;
  ExprList *pEList;
  SrcList *pTabList;
  Expr *pWhere;
  ExprList *pGroupBy;
  Expr *pHaving;
  int rc = 1;
  DistinctCtx sDistinct;
  SortCtx sSort;
  AggInfo sAggInfo;
  sqlite3 *db;
  int iRestoreSelectId = pParse->iSelectId;
  sqlite3SelectPrep(pParse, p, 0);
  for (i = 0; !p->pPrior && i < pTabList->nSrc; i++) {
    struct SrcList_item *pItem = &pTabList->a[i];
    int isAggSub;
    if (pItem->addrFillSub) {
      int addrTop = sqlite3VdbeCurrentAddr(v) + 1;
      int topAddr;
      int onceAddr = 0;
      int retAddr;
    }
    KeyInfo *pKeyInfo;
    u16 wctrlFlags = sDistinct.isTnct ? WHERE_WANT_DISTINCT : 0;
    selectInnerLoop(pParse, p, pEList, -1, &sSort, &sDistinct, pDest,
                    sqlite3WhereContinueLabel(pWInfo),
                    sqlite3WhereBreakLabel(pWInfo));
    int iAMem;
    int iBMem;
    int iUseFlag;
    int iAbortFlag;
    int groupBySort;
    int sortOut = 0;
    if (pGroupBy) {
      int addrSortingIdx;
      int addrReset;
      sqlite3VdbeAddOp4(v, OP_Compare, iAMem, iBMem, pGroupBy->nExpr,
                        (char *)sqlite3KeyInfoRef(pKeyInfo), P4_KEYINFO);
      ExprList *pDel = 0;
      Table *pTab;
      if (pTab = isSimpleCount(p, &sAggInfo) != 0) {
        const int iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
        Index *pIdx;
        int iRoot = pTab->tnum;
        for (pIdx = pTab->pIndex; pIdx; pIdx = pIdx->pNext) {
          sqlite3VdbeAddOp2(v, OP_Goto, 0, sqlite3WhereBreakLabel(pWInfo));
        }
      }
    }
  };
}
void sqlite3Insert(Parse *pParse, SrcList *pTabList, Select *pSelect,
                   IdList *pColumn, int onError) {
  sqlite3 *db;
  Table *pTab;
  int i, j, idx;
  Vdbe *v;
  Index *pIdx;
  int nColumn;
  int nHidden = 0;
  int iDataCur = 0;
  int iIdxCur = 0;
  int ipkColumn = -1;
  int endOfLoop;
  int srcTab = 0;
  SelectDest dest;
  Db *pDb;
  u8 useTempTable = 0;
  ExprList *pList = 0;
  int regRowCount = 0;
  int regIns;
  int regRowid;
  int *aRegIdx = 0;
  int tmask;
  if (pSelect) {
    int rc;
    rc = sqlite3Select(pParse, pSelect, &dest);
    nColumn = pList ? pList->nExpr : 0;
    int nIdx;
    int regCols = sqlite3GetTempRange(pParse, pTab->nCol + 1);
    if (ipkColumn < 0) {
      int j1;
      const char *pVTab = (const char *)sqlite3GetVTable(db, pTab);
      sqlite3VdbeChangeP5(v, onError == OE_Default ? OE_Abort : onError);
      int isReplace;
      sqlite3GenerateConstraintChecks(pParse, pTab, aRegIdx, iDataCur, iIdxCur,
                                      regIns, 0, ipkColumn >= 0, onError,
                                      endOfLoop, &isReplace);
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
int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  Parse *pParse;
  char *zErrMsg = 0;
  pParse = sqlite3StackAllocZero(db, sizeof *pParse);
  pParse->db = db;
  if (nBytes >= 0 && nBytes == 0 || zSql[nBytes - 1] != 0)
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
    *ppStmt = (sqlite3_stmt *)pParse->pVdbe;
  }
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
    if (strcmp(z, "-separator") == 0 || strcmp(z, "-nullvalue") == 0 ||
        strcmp(z, "-cmd") == 0)
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
}
