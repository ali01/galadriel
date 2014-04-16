#include "for_stmt.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "../../expr/expr.h"

ForStmt::ForStmt(Expr::Ptr init, Expr::Ptr test,
                 Expr::Ptr step, Stmt::Ptr body) :
  LoopStmt(test, body), init_(init), step_(step)
{
  assert(init_ != NULL && test != NULL && step_ != NULL && body != NULL);
}

Expr::Ptr
ForStmt::init() {
  return init_;
}

Expr::PtrConst
ForStmt::init() const {
  return init_;
}


Expr::Ptr
ForStmt::step() {
  return step_;
}

Expr::PtrConst
ForStmt::step() const {
  return step_;
}
