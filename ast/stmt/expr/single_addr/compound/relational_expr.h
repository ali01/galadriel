#ifndef RELATIONAL_EXPR_H_4GKQLWZF
#define RELATIONAL_EXPR_H_4GKQLWZF

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/single_addr/compound */
#include "compound_expr.h"

/* forward declarations */
class Operator;
class Location;

class RelationalExpr : public CompoundExpr {
public:
  typedef Simone::Ptr<const RelationalExpr> PtrConst;
  typedef Simone::Ptr<RelationalExpr> Ptr;

  static Ptr RelationalExprNew(Expr::Ptr lhs,
                               Simone::Ptr<Operator> op,
                               Expr::Ptr rhs) {
    return new RelationalExpr(lhs, op, rhs);
  }

  RelationalExpr(Expr::Ptr lhs,
                 Simone::Ptr<Operator> op,
                 Expr::Ptr rhs);

  Simone::Ptr<const Type> type() const;

  Simone::Ptr<Location> auxLocation() const;
  void auxLocationIs(Simone::Ptr<Location> _loc);

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Simone::Ptr<Location> aux_loc_;
};

#endif
