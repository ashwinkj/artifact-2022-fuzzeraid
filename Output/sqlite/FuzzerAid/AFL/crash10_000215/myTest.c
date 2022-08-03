#include "src/he_select.h"
int withExpand(Walker *pWalker, struct SrcList_item *pFrom) {
  struct Cte *pCte;
  if (pCte) {
    ExprList *pEList;
    int bMayRecursive;
    if (bMayRecursive) {
      if (pEList->nExpr != pCte->pCols->nExpr) {
      }
    }
  }
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
  sqlite3WithPush(pParse, findRightmost(p)->pWith, 0);
  for (i = 0, pFrom = pTabList->a; i < pTabList->nSrc; i++, pFrom++) {
    Table *pTab;
    if (withExpand(pWalker, pFrom))
      if (pFrom->pTab)
        ;
    struct ExprList_item *a = pEList->a;
    ExprList *pNew = 0;
    int flags = pParse->db->flags;
    int longNames = (flags & SQLITE_FullColNames) != 0 &&
                    (flags & SQLITE_ShortColNames) == 0;
    for (k = 0; k < pEList->nExpr; k++)
      ;
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
  sqlite3 *db;
  int iRestoreSelectId = pParse->iSelectId;
  sqlite3SelectPrep(pParse, p, 0);
  if (pParse->nErr || db->mallocFailed)
    ;
}
void sqlite3Insert(Parse *pParse, SrcList *pTabList, Select *pSelect,
                   IdList *pColumn, int onError) {
  sqlite3 *db;
  Table *pTab;
  char *zTab;
  const char *zDb;
  int i, j, idx;
  Vdbe *v;
  Index *pIdx;
  int nColumn;
  int nHidden = 0;
  int iDataCur = 0;
  int iIdxCur = 0;
  int ipkColumn = -1;
  int endOfLoop;

  SelectDest dest;

  Db *pDb;
  u8 bIdListInOrder = 1;
  ExprList *pList = 0;

  int *aRegIdx = 0;
  int isView;
  Trigger *pTrigger;
  int tmask;
  pTrigger = sqlite3TriggersExist(pParse, pTab, TK_INSERT, 0, &tmask);
  if (IsVirtual(pTab))
    ;
  if (pColumn)
    ;
  if (pSelect) {
    int regYield;
    int rc;
    rc = sqlite3Select(pParse, pSelect, &dest);
    int nIdx;
    nIdx = sqlite3OpenTableAndIndices(pParse, pTab, OP_OpenWrite, -1, 0,
                                      &iDataCur, &iIdxCur);
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
#include "src/he_mem1.h"
void *sqlite3MemMalloc(int nByte);
Select *sqlite3SelectNew(Parse *pParse, ExprList *pEList, SrcList *pSrc,
                         Expr *pWhere, ExprList *pGroupBy, Expr *pHaving,
                         ExprList *pOrderBy, u16 selFlags, Expr *pLimit,
                         Expr *pOffset);

SrcList *sqlite3SrcListAppendFromTerm(Parse *pParse, SrcList *p, Token *pTable,
                                      Token *pDatabase, Token *pAlias,
                                      Select *pSubquery, Expr *pOn,
                                      IdList *pUsing) {
  if (p == 0 || NEVER(p->nSrc == 0))
    ;
}
SrcList *sqlite3SrcListAppend(sqlite3 *db, SrcList *pList, Token *pTable,
                              Token *pDatabase);
SrcList *sqlite3SrcListEnlarge(sqlite3 *db, SrcList *pSrc, int nExtra,
                               int iStart);
int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i;
  void *pEngine;
  int tokenType;
  sqlite3 *db = pParse->db;
  int mxSqlLen;
  i = 0;
  pEngine = sqlite3ParserAlloc((void *(*)(size_t))sqlite3Malloc);
  while (!db->mallocFailed && zSql[i] != 0) {
    pParse->sLastToken.z = &zSql[i];
    pParse->sLastToken.n =
        sqlite3GetToken((unsigned char *)&zSql[i], &tokenType);
    i += pParse->sLastToken.n;
    if (i > mxSqlLen)
      ;
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
  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
  pParse->db = db;
  if (nBytes >= 0 && (nBytes == 0 || zSql[nBytes - 1] != 0))
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
  }
}
#include "src/he_btree.h"
int sqlite3BtreeSchemaLocked(Btree *p);
int querySharedCacheTableLock(Btree *p, Pgno iTab, u8 eLock);
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
int sqlite3_finalize(sqlite3_stmt *pStmt) {
  if (pStmt == 0)
    ;
}
#include "src/he_shell.h"
int main(int argc, char **argv) {
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
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
  if (rc > 0)
    ;
}
