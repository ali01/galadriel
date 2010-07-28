#ifndef WHILE_STMT_H_WOMFWW9H
#define WHILE_STMT_H_WOMFWW9H

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/conditional/loop includes */
#include "loop_stmt.h"

/* forward declarations */
class Expr;

class WhileStmt : public LoopStmt  {
public:
  typedef Simone::Ptr<const WhileStmt> PtrConst;
  typedef Simone::Ptr<WhileStmt> Ptr;

  static Ptr WhileStmtNew(Simone::Ptr<Expr> test, Stmt::Ptr body) {
    return new WhileStmt(test, body);
  }

  WhileStmt(Simone::Ptr<Expr> test, Stmt::Ptr body) : LoopStmt(test, body) {}

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }
};

#endif
