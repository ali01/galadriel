#include "return_stmt.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "expr/expr.h"

ReturnStmt::ReturnStmt(yyltype _loc, Expr::Ptr _expr) :
  Stmt(_loc), expr_(_expr)
{
  assert(expr_ != NULL);
}

Expr::Ptr
ReturnStmt::expr() {
  return expr_;
}

Expr::PtrConst
ReturnStmt::expr() const {
  return expr_;
}
