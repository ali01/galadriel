#include "return_stmt.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "expr/expr.h"

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc), expr(e) {
  assert(e != NULL);
}
