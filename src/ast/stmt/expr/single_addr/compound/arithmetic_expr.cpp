#include "arithmetic_expr.h"

/* ast includes */
#include "../../../../operator.h"

/* ast/stmt/expr/singl_addr/compound includes */
#include "compound_expr.h"

ArithmeticExpr::ArithmeticExpr(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs) :
  CompoundExpr(lhs,op,rhs) {}
