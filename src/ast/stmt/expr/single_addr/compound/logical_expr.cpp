#include "logical_expr.h"

/* code_generator includes */
#include <code_generator/location/location.h>

/* ast includes */
#include "../../../../operator.h"
#include "../../../../type/type.h"

LogicalExpr::LogicalExpr(Expr::Ptr lhs,
                         Operator::Ptr op,
                         Expr::Ptr rhs) : 
  CompoundExpr(lhs,op,rhs) {}

Type::PtrConst
LogicalExpr::type() const {
  return Type::kBool;
}

Location::PtrConst
LogicalExpr::location() {
  return NULL; // TODO
}
