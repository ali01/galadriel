#include "conditional_stmt.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "../expr/expr.h"

/* ast/stmt includes */
#include "../stmt.h"

ConditionalStmt::ConditionalStmt(Expr::Ptr t, Stmt::Ptr b) :
  Stmt(), test_(t), body_(b)
{
  assert(test_ != NULL && body_ != NULL);
}

Expr::PtrConst
ConditionalStmt::test() const {
  return test_;
}

Stmt::PtrConst
ConditionalStmt::body() const {
  return body_;
}

Expr::Ptr
ConditionalStmt::test() {
  return test_;
}

Stmt::Ptr
ConditionalStmt::body() {
  return body_;
}
