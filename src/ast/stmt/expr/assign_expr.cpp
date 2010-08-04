#include "assign_expr.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* ast/stmt/expr/single_addr includes */
#include "single_addr/single_addr_expr.h"
#include "single_addr/l_value/l_value_expr.h"

AssignExpr::AssignExpr(Expr::Ptr lhs, Expr::Ptr rhs) :
  Expr(Join(lhs->lexLoc(), rhs->lexLoc())), left_(lhs), right_(rhs)
{
  assert(lhs != NULL && rhs != NULL);
}
