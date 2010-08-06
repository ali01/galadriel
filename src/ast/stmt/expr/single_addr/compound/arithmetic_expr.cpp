#include "arithmetic_expr.h"

/* ast includes */
#include "../../../../operator.h"

/* ast/type includes */
#include "../../../../type/type.h"

/* ast/stmt/expr/singl_addr/compound includes */
#include "compound_expr.h"

ArithmeticExpr::ArithmeticExpr(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs) :
  CompoundExpr(lhs, op, rhs) {}

Type::PtrConst
ArithmeticExpr::type() const {
  Type::PtrConst type = right_->type();

  if (left_) {
    if (left_->type() != right_->type())
      type = Type::kError;

    if (left_->type() != Type::kInt && left_->type() != Type::kDouble)
      type = Type::kError;
  }

  return type;
}
