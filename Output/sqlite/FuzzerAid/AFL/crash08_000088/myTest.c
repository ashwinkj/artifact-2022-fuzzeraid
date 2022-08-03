#include "src/he_vtab.h"
int sqlite3VtabCallCreate(sqlite3 *db, int iDb, const char *zTab,
                          char **pzErr) {
  Table *pTab;
  const char *zMod;
  zMod = pTab->azModuleArg[0];
}
#include "src/he_vdbe.h"
int sqlite3VdbeExec(Vdbe *p) {
  int pc = 0;
  Op *aOp = p->aOp;
  Op *pOp;
  int rc = SQLITE_OK;
  sqlite3 *db = p->db;
  for (pc = p->pc; rc == SQLITE_OK; pc++) {
    pOp = &aOp[pc];
    switch (pOp->opcode) {
    case OP_Halt: {
      rc = sqlite3VtabCallCreate(db, pOp->p1, pOp->p4.z, &p->zErrMsg);
    }
    }
  }
}
int sqlite3_step(sqlite3_stmt *pStmt) {
  int rc = SQLITE_OK;
  int rc2 = SQLITE_OK;
  Vdbe *v = (Vdbe *)pStmt;
  while (rc = sqlite3Step(v) == SQLITE_SCHEMA &&
              (rc2 = rc = sqlite3Reprepare(v)) == SQLITE_OK)
    ;
}
int sqlite3Step(Vdbe *p) {
  int rc;
  { rc = sqlite3VdbeExec(p); }
}
#include "src/he_shell.h"
int main(int argc, char **argv) {
  struct callback_data data;
  const char *zInitFile = 0;
  int i, rc = 0;
  for (i = 1; i < argc; i++) {
    char *z;
    z = argv[i];
    if (z[0] != '-')
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
    data.zDbFilename = ":memory:";
  }
  rc = process_sqliterc(&data, zInitFile);
}
