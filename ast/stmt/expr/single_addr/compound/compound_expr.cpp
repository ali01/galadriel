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
  SingleAddrExpr(Join(l->lexLoc(), r->lexLoc())), op_(o), left_(l), right_(r)
{
  assert(l != NULL && o != NULL && r != NULL);
}

CompoundExpr::CompoundExpr(Operator::Ptr o, Expr::Ptr r) :
  SingleAddrExpr(Join(o->lexLoc(), r->lexLoc())), op_(o), left_(NULL), right_(r)
{
  assert(o != NULL && r != NULL);
}

Operator::Ptr
CompoundExpr::op() {
  return op_;
}

Operator::PtrConst
CompoundExpr::op() const {
  return op_;
}
