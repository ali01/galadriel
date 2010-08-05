#include "arithmetic_expr.h"

/* ast includes */
#include "../../../../operator.h"

/* ast/type includes */
#include "../../../../type/type.h"

/* ast/stmt/expr/singl_addr/compound includes */
#include "compound_expr.h"

ArithmeticExpr::ArithmeticExpr(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs) :
  CompoundExpr(lhs,op,rhs) {}

Type::PtrConst
ArithmeticExpr::type() const {
  Type::PtrConst type = left->type();

  if (left->type() != right->type())
    type = Type::kError;

  if (left->type() != Type::kInt && left->type() != Type::kDouble)
    type = Type::kError;

  return type;
}
