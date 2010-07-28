#ifndef RELATIONAL_EXPR_H_4GKQLWZF
#define RELATIONAL_EXPR_H_4GKQLWZF

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/single_addr/compound */
#include "compound_expr.h"

/* forward declarations */
class Operator;

class RelationalExpr : public CompoundExpr {
public:
  typedef Simone::Ptr<const RelationalExpr> PtrConst;
  typedef Simone::Ptr<RelationalExpr> Ptr;

  static Ptr RelationalExprNew(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs) {
    return new RelationalExpr(lhs, op, rhs);
  }

  RelationalExpr(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }
};

#endif
