#include "logical_expr.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast includes */
#include "../../../../operator.h"
#include "../../../../type/type.h"

LogicalExpr::LogicalExpr(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs) : 
  CompoundExpr(lhs,op,rhs) {}

Type::PtrConst
LogicalExpr::type() const {
  return Type::kBool;
}

Location::Ptr
LogicalExpr::auxLocation() const {
  return aux_loc_;
}

void
LogicalExpr::auxLocationIs(Location::Ptr _loc) {
  aux_loc_ = _loc;
}
