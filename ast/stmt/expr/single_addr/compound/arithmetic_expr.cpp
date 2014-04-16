#include "arithmetic_expr.h"

/* ast includes */
#include "../../../../operator.h"

/* ast/type includes */
#include "../../../../type/type.h"

/* ast/stmt/expr/single_addr includes */
#include "../int_const_expr.h"

ArithmeticExpr::ArithmeticExpr(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs) :
  CompoundExpr(lhs, op, rhs) {}

ArithmeticExpr::ArithmeticExpr(Operator::Ptr op, Expr::Ptr rhs) :
  CompoundExpr(IntConstExpr::IntConstExprNew(0), op, rhs)
{
  assert(op && rhs);
  /* if unary minus, lhs is set to an
     int_const_expr that evaluates to zero */
}

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
