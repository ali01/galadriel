#include "for_stmt.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "../../expr/expr.h"

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b) :
  LoopStmt(t, b), init(i), step(s)
{
  assert(i != NULL && t != NULL && s != NULL && b != NULL);
}
