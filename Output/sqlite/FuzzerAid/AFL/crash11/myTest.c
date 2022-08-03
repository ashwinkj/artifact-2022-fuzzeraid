#include "src/he_where.h"
i8 wherePathSatisfiesOrderBy(WhereInfo *pWInfo, ExprList *pOrderBy,
                             WherePath *pPath, u16 wctrlFlags, u16 nLoop,
                             WhereLoop *pLast, Bitmask *pRevMask) {
  u8 revSet;
  u8 rev;
  u8 isOrderDistinct;
  int iLoop;
  WhereLoop *pLoop = 0;
  Bitmask obSat = 0;
  Bitmask obDone;
  for (iLoop = 0; isOrderDistinct && obSat < obDone && iLoop <= nLoop;
       iLoop++) {
    if (pLoop->wsFlags & WHERE_VIRTUALTABLE) {
    }
  }
}
int wherePathSolver(WhereInfo *pWInfo, LogEst nRowEst) {
  int mxChoice, nLoop, ii, jj, nTo, nFrom;
  Parse *pParse;
  sqlite3 *db;
  int iLoop;
  int mxI = 0;
  int nOrderBy;
  LogEst rCost;
  LogEst mxCost = 0;
  LogEst mxOut = 0;
  WherePath *aFrom;
  WherePath *aTo;
  WherePath *pFrom;
  WherePath *pTo;
  WhereLoop *pWLoop;
  WhereLoop **pX;
  char *pSpace;
  aTo = (WherePath *)pSpace;
  for (ii = mxChoice * 2, pFrom = aTo; ii > 0; ii--, pFrom++, pX += nLoop) {
    for (ii = 0, pFrom = aFrom; ii < nFrom; ii++, pFrom++) {
      for (pWLoop = pWInfo->pLoops; pWLoop; pWLoop = pWLoop->pNextLoop) {
        Bitmask revMask = 0;
        i8 isOrdered = pFrom->isOrdered;
        if (isOrdered < 0) {
          isOrdered = wherePathSatisfiesOrderBy(pWInfo, pWInfo->pOrderBy, pFrom,
                                                pWInfo->wctrlFlags, iLoop,
                                                pWLoop, &revMask);
        }
      }
    }
    Bitmask notUsed;
    int rc = wherePathSatisfiesOrderBy(pWInfo, pWInfo->pResultSet, pFrom,
                                       WHERE_DISTINCTBY, nLoop - 1,
                                       pFrom->aLoop[nLoop - 1], &notUsed);
  }
  if (pWInfo->pOrderBy) {
    if (pWInfo->wctrlFlags & WHERE_DISTINCTBY)
      ;
    else {
      Bitmask notUsed = 0;
      int nOrder = wherePathSatisfiesOrderBy(pWInfo, pWInfo->pOrderBy, pFrom, 0,
                                             nLoop - 1, pFrom->aLoop[nLoop - 1],
                                             &notUsed);
    }
  }
}
void *sqlite3DbMallocRaw(sqlite3 *db, int n) {
  void *p;
  p = sqlite3Malloc(n);
  return p;
}
WhereInfo *sqlite3WhereBegin(Parse *pParse, SrcList *pTabList, Expr *pWhere,
                             ExprList *pOrderBy, ExprList *pResultSet,
                             u16 wctrlFlags, int iIdxCur) {
  int nByteWInfo;
  int nTabList;
  WhereInfo *pWInfo;
  Vdbe *v = pParse->pVdbe;
  Bitmask notReady;
  WhereLoopBuilder sWLB;
  WhereMaskSet *pMaskSet;
  WhereLevel *pLevel;
  WhereLoop *pLoop;
  int ii;
  sqlite3 *db;
  int rc;
  pWInfo = sqlite3DbMallocZero(db, nByteWInfo + sizeof(WhereLoop));
  pWInfo->pOrderBy = pOrderBy;
  if (nTabList != 1 || whereShortCut(&sWLB) == 0) {
    if (pWInfo->pOrderBy) {
      wherePathSolver(pWInfo, pWInfo->nRowOut + 1);
    }
    while (pWInfo->nLevel >= 2) {
      WhereTerm *pTerm, *pEnd;
    }
    Table *pTab;
  }
}
#include "src/he_select.h"
int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  int i, j, isAgg;
  WhereInfo *pWInfo;
  Vdbe *v;
  ExprList *pEList;
  SrcList *pTabList;
  Expr *pWhere;
  ExprList *pGroupBy;
  DistinctCtx sDistinct;
  SortCtx sSort;
  AggInfo sAggInfo;
  sqlite3 *db;
  int iRestoreSelectId = pParse->iSelectId;
  memset(&sAggInfo, 0, sizeof(sAggInfo));
  if (checkForMultiColumnSelectError(pParse, pDest, pEList->nExpr)) {
    struct SrcList_item *pItem = &pTabList->a[i];
    int isAggSub;
  }
  if (p->selFlags & (SF_Distinct | SF_Aggregate) == SF_Distinct &&
      sqlite3ExprListCompare(sSort.pOrderBy, p->pEList, -1) == 0) {
    u16 wctrlFlags = sDistinct.isTnct ? WHERE_WANT_DISTINCT : 0;
    selectInnerLoop(pParse, p, pEList, -1, &sSort, &sDistinct, pDest,
                    sqlite3WhereContinueLabel(pWInfo),
                    sqlite3WhereBreakLabel(pWInfo));
  } else {
    int iAMem;
    int orderByGrp = 0;
    if (pGroupBy) {
      pWInfo = sqlite3WhereBegin(pParse, pTabList, pWhere, pGroupBy, 0,
                                 WHERE_GROUPBY | 0, 0);
    }
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
    default: {
      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
    }
    }
  };
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
    if (strcmp(z, "-separator") == 0 || strcmp(z, "-nullvalue") == 0 ||
        strcmp(z, "-cmd") == 0)
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
}
