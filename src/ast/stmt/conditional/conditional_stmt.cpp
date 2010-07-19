#include "conditional_stmt.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "../expr/expr.h"

/* ast/stmt includes */
#include "../stmt.h"

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) :
  Stmt(), test(t), body(b)
{
  assert(test != NULL && body != NULL);
}
