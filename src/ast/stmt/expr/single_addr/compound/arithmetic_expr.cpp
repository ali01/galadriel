#include "arithmetic_expr.h"

/* ast/stmt/expr/singl_addr/compound includes */
#include "compound_expr.h"

ArithmeticExpr::ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) :
  CompoundExpr(lhs,op,rhs) {}
