#ifndef ASSIGNMENT_EXPR_H_CIV2NE6Y
#define ASSIGNMENT_EXPR_H_CIV2NE6Y

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Expr;
class Location;
class LValueExpr;
class Operator;
class Type;

class AssignExpr : public Expr {
public:
  typedef Simone::Ptr<const AssignExpr> PtrConst;
  typedef Simone::Ptr<AssignExpr> Ptr;

  static Ptr AssignExprNew(Simone::Ptr<LValueExpr> _l_val,
                           Simone::Ptr<Operator> _op,
                           Expr::Ptr _rhs) {
    return new AssignExpr(_l_val, _op, _rhs);
  }

  AssignExpr(Simone::Ptr<LValueExpr> _l_val,
             Simone::Ptr<Operator> _op,
             Expr::Ptr _rhs);

  /* -- attribute member functions -- */

  /* const interface */
  Simone::Ptr<const LValueExpr> left() const { return l_value_; }
  Simone::Ptr<const Operator> op() const { return op_; }
  Expr::PtrConst right() const { return right_; }

  /* non-const interface */
  Simone::Ptr<LValueExpr> left() { return l_value_; }
  Simone::Ptr<Operator> op() { return op_; }
  Expr::Ptr right() { return right_; }

  Simone::Ptr<const Type> type() const;
  Simone::Ptr<Location> location();

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Simone::Ptr<LValueExpr> l_value_;
  Simone::Ptr<Operator> op_;
  Expr::Ptr right_;
};

#endif
