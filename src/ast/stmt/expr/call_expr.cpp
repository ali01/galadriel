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

CallExpr::CallExpr(yyltype loc, Expr *b, Identifier *f, Deque<Expr*>::Ptr a) :
  Expr(loc), field(f), actuals(a)
{
  /* b can be null (just means no explicit base) */
  assert(f != NULL && a != NULL);
  base = b;
}
