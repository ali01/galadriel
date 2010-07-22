#include "call_expr.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "../../identifier.h"

/* ast/stmt/expr includes */
#include "expr.h"

CallExpr::CallExpr(yyltype loc,
                   Expr::Ptr base,
                   Identifier::Ptr field,
                   Deque<Expr::Ptr>::Ptr args) :
  Expr(loc), base(base), field(field), actuals(args)
{
  /* b can be null (just means no explicit base) */
  assert(field != NULL && args != NULL);
}
