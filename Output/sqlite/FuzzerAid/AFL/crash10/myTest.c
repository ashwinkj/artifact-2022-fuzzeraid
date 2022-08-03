#include "src/he_select.h"
int withExpand(Walker *pWalker, struct SrcList_item *pFrom) {
  Parse *pParse = pWalker->pParse;
  struct Cte *pCte;
  With *pWith;
  pCte = searchWith(pParse->pWith, pFrom, &pWith);
  if (pCte) {
    ExprList *pEList;
    if (pCte->pCols) {
      if (pEList->nExpr != pCte->pCols->nExpr) {
      }
    }
  }
  return SQLITE_OK;
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
  int i, j, k;
  SrcList *pTabList;
  struct SrcList_item *pFrom;
  Expr *pE, *pRight, *pExpr;
  pTabList = p->pSrc;
  for (i = 0, pFrom = pTabList->a; i < pTabList->nSrc; i++, pFrom++) {
    if (withExpand(pWalker, pFrom))
      if (pFrom->pTab)
        ;
  }
}
void sqlite3SelectExpand(Parse *pParse, Select *pSelect) {
  Walker w;
  w.pParse = pParse;
  w.xSelectCallback = selectExpander;
  sqlite3WalkSelect(&w, pSelect);
}
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  sqlite3SelectExpand(pParse, p);
}
int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  int i, j;
  WhereInfo *pWInfo;
  ExprList *pEList;
  SrcList *pTabList;
  Expr *pWhere;
  ExprList *pGroupBy;
  int rc = 1;
  DistinctCtx sDistinct;
  SortCtx sSort;
  AggInfo sAggInfo;
  sqlite3SelectPrep(pParse, p, 0);
  for (i = 0; !p->pPrior && i < pTabList->nSrc; i++) {
    u16 wctrlFlags = (sDistinct.isTnct ? WHERE_WANT_DISTINCT : 0);
    pWInfo = sqlite3WhereBegin(pParse, pTabList, pWhere, sSort.pOrderBy,
                               p->pEList, wctrlFlags, 0);
    selectInnerLoop(pParse, p, pEList, -1, &sSort, &sDistinct, pDest,
                    sqlite3WhereContinueLabel(pWInfo),
                    sqlite3WhereBreakLabel(pWInfo));
    if (pGroupBy) {
      if (sqlite3WhereIsOrdered(pWInfo) == pGroupBy->nExpr) {
        explainTempTable(pParse,
                         (sDistinct.isTnct && (p->selFlags & SF_Distinct) == 0)
                             ? "DISTINCT"
                             : "GROUP BY");
      }
    }
  }
}
void sqlite3Insert(Parse *pParse, SrcList *pTabList, Select *pSelect,
                   IdList *pColumn, int onError) {
  Table *pTab;
  int iDataCur = 0;
  int iIdxCur = 0;
  int ipkColumn = -1;
  int endOfLoop;
  SelectDest dest;
  int regIns;
  int *aRegIdx = 0;
  if (pSelect) {
    int rc;
    rc = sqlite3Select(pParse, pSelect, &dest);
    if (IsVirtual(pTab))
      ;
  }
}
#include "src/he_vdbeaux.h"

void *sqlite3Malloc(int n);
#include "src/he_mem1.h"

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
#include "src/he_tokenize.h"
int sqlite3GetToken(const unsigned char *z, int *tokenType);
void sqlite3ExprListSetSpan(Parse *pParse, ExprList *pList, ExprSpan *pSpan);

int sqlite3Prepare(sqlite3 *db, const char *zSql, int nBytes, int saveSqlFlag,
                   Vdbe *pReprepare, sqlite3_stmt **ppStmt,
                   const char **pzTail) {
  Parse *pParse;
  char *zErrMsg = 0;
  int rc = SQLITE_OK;
  int i;
  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
  for (i = 0; i < db->nDb; i++)
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
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
}
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
}
#include "src/he_os.h"

#include "src/he_shell.h"
int main(int argc, char **argv) {
  struct callback_data data;
  const char *zInitFile = 0;
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
  if (rc > 0)
    ;
}
