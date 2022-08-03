#include "src/he_build.h"
void convertToWithoutRowidTable(Parse *pParse, Table *pTab) {
  Index *pPk;
  pPk->isCovering = 1;
}
void sqlite3EndTable(Parse *pParse, Token *pCons, Token *pEnd, u8 tabOpts,
                     Select *pSelect) {
  Table *p;
  p = pParse->pNewTable;
  if (tabOpts & TF_WithoutRowid) {
    if (p->tabFlags & TF_Autoincrement)
      ;
    else {
      convertToWithoutRowidTable(pParse, p);
    }
  }
}
int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i, tokenType, lastTokenParsed = -1;
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
    if (lastTokenParsed != TK_SEMI) {
      pParse->zTail = &zSql[i];
    }
  }
}
int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  *ppStmt = 0;
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
  return rc;
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
    if (z[0] != '-')
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    } else if (strcmp(z, "-batch") == 0)
      ;
  }
  rc = process_sqliterc(&data, zInitFile);
}
