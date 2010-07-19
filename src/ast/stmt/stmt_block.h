#ifndef STMT_BLOCK_H_KT25NQCB
#define STMT_BLOCK_H_KT25NQCB

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast/stmt includes */
#include "stmt.h"

/* forward declarations */
class Stmt;
class VarDecl;

class StmtBlock : public Stmt {
public:
  StmtBlock(Deque<VarDecl*>::Ptr variableDeclarations,
            Deque<Stmt*>::Ptr statements);

private:
  /* data members */
  Deque<VarDecl*>::Ptr decls;
  Deque<Stmt*>::Ptr stmts;
};

#endif
