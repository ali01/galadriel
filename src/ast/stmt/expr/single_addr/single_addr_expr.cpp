#include "single_addr_expr.h"

/* code_generator/location includes */
#include <code_generator/location/location.h>

SingleAddrExpr::SingleAddrExpr(yyltype loc) : Expr(loc) {}

SingleAddrExpr::~SingleAddrExpr() {}

void
SingleAddrExpr::locationIs(Simone::Ptr<const Location> _loc) {
  location_ = _loc;
}
