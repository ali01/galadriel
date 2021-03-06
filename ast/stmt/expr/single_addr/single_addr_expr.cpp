#include "single_addr_expr.h"

/* code_generator/location includes */
#include <code_generator/location_includes.h>

SingleAddrExpr::SingleAddrExpr(yyltype loc) : Expr(loc) {}

SingleAddrExpr::~SingleAddrExpr() {}

Location::Ptr
SingleAddrExpr::location() const {
  return location_;
}

void
SingleAddrExpr::locationIs(Simone::Ptr<Location> _loc) {
  location_ = _loc;
}
