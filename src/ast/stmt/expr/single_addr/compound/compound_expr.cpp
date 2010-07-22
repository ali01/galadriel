#include "compound_expr.h"

/* simone includes */
#include <simone/utility.h>

/* ast includes */
#include "../../../../operator.h"

/* expr includes */
#include "../../expr.h"

/* single-addr includes */
#include "../single_addr_expr.h"

CompoundExpr::CompoundExpr(Expr::Ptr l, Operator::Ptr o, Expr::Ptr r) :
  SingleAddrExpr(Join(l->lexLoc(), r->lexLoc())), op(o), left(l), right(r)
{
  assert(l != NULL && o != NULL && r != NULL);
}

CompoundExpr::CompoundExpr(Operator::Ptr o, Expr::Ptr r) :
  SingleAddrExpr(Join(o->lexLoc(), r->lexLoc())), op(o), left(NULL), right(r)
{
  assert(o != NULL && r != NULL);
}

CompoundExpr::CompoundExpr(Expr::Ptr lhs, Operator::Ptr o) :
  SingleAddrExpr(Join(o->lexLoc(), lhs->lexLoc())),
  op(o), left(lhs), right(NULL)
{
  assert(o != NULL && lhs != NULL);
}
