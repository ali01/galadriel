#include "assignment_expr.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* ast/stmt/expr/single_addr includes */
#include "single_addr/single_addr_expr.h"
#include "single_addr/l_value/l_value_expr.h"

AssignExpr::AssignExpr(Expr *l, Expr *r) :
  Expr(Join(l->lexLoc(), r->lexLoc())), left(l), right(r)
{
  assert(l != NULL && r != NULL);
}
