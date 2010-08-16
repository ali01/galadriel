#include "relational_expr.h"

/* code_generator includes */
#include <code_generator/location/location.h>

/* ast includes */
#include "../../../../operator.h"

/* ast/type includes */
#include "../../../../type/type.h"

RelationalExpr::RelationalExpr(Expr::Ptr lhs,
                               Operator::Ptr op,
                               Expr::Ptr rhs) :
  CompoundExpr(lhs,op,rhs) {}

Type::PtrConst
RelationalExpr::type() const {
  return Type::kBool;
}

Location::Ptr
RelationalExpr::location() {
  return NULL;
}
