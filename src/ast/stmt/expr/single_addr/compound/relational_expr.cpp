#include "relational_expr.h"

RelationalExpr::RelationalExpr(Expr::Ptr lhs,
                               Simone::Ptr<Operator> op,
                               Expr::Ptr rhs) :
  CompoundExpr(lhs,op,rhs) {}
