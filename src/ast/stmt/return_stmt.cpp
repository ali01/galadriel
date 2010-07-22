#include "return_stmt.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "expr/expr.h"

ReturnStmt::ReturnStmt(yyltype loc, Simone::Ptr<Expr> expr) :
  Stmt(loc), expr(expr)
{
  assert(expr != NULL);
}
