#include "relational_expr.h"

/* ast/type includes */
#include "../../../../type/type.h"

RelationalExpr::RelationalExpr(Expr::Ptr lhs,
                               Simone::Ptr<Operator> op,
                               Expr::Ptr rhs) :
  CompoundExpr(lhs,op,rhs) {}

Type::PtrConst
RelationalExpr::type() const {
  return Type::kBool;
}
