#include "relational_expr.h"

RelationalExpr::RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) :
  CompoundExpr(lhs,op,rhs) {}
