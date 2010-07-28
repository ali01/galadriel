#include "if_stmt.h"

/* ast/stmt includes */
#include "../stmt.h"

/* ast/stmt/expr includes */
#include "../expr/expr.h"

/* ast/stmt/conditional includes */
#include "conditional_stmt.h"

IfStmt::IfStmt(Expr::Ptr test, Stmt::Ptr then_body, Stmt::Ptr else_body) :
  ConditionalStmt(test, then_body), else_body_(else_body)
{
  // elseBody can be NULL
}
