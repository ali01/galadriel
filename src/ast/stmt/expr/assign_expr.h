#ifndef ASSIGNMENT_EXPR_H_CIV2NE6Y
#define ASSIGNMENT_EXPR_H_CIV2NE6Y

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Expr;
class LValueExpr;
class Type;

class AssignExpr : public Expr {
public:
  typedef Simone::Ptr<const AssignExpr> PtrConst;
  typedef Simone::Ptr<AssignExpr> Ptr;

  static Ptr AssignExprNew(Simone::Ptr<LValueExpr> l_val, Expr::Ptr rhs) {
    return new AssignExpr(l_val, rhs);
  }

  AssignExpr(Simone::Ptr<LValueExpr> l_val, Expr::Ptr rhs);

  /* -- attribute member functions -- */

  /* const interface */
  Simone::Ptr<const LValueExpr> left() const { return l_value_; }
  Expr::PtrConst right() const { return right_; }

  /* non-const interface */
  Simone::Ptr<LValueExpr> left() { return l_value_; }
  Expr::Ptr right() { return right_; }

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Simone::Ptr<LValueExpr> l_value_;
  Expr::Ptr right_;
};

#endif
