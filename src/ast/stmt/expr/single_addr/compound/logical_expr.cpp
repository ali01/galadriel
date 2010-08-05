#include "logical_expr.h"

/* ast includes */
#include "../../../../operator.h"
#include "../../../../type/type.h"

LogicalExpr::LogicalExpr(Expr::Ptr lhs,
                         Simone::Ptr<Operator> op,
                         Expr::Ptr rhs) : 
  CompoundExpr(lhs,op,rhs) {}

Type::PtrConst
LogicalExpr::type() const {
  return Type::kBool;
}
