#ifndef ASSIGNMENT_EXPR_H_CIV2NE6Y
#define ASSIGNMENT_EXPR_H_CIV2NE6Y

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Expr;

class AssignExpr : public Expr {
public:
  typedef Simone::Ptr<const AssignExpr> PtrConst;
  typedef Simone::Ptr<AssignExpr> Ptr;

  static Ptr AssignExprNew(Expr::Ptr lhs, Expr::Ptr rhs) {
    return new AssignExpr(lhs, rhs);
  }

  AssignExpr(Expr::Ptr lhs, Expr::Ptr rhs);

  /* -- attribute member functions -- */

  /* const interface */
  Expr::PtrConst left() const { return left_; }
  Expr::PtrConst right() const { return right_; }

  /* non-const interface */
  Expr::Ptr left() { return left_; }
  Expr::Ptr right() { return right_; }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Expr::Ptr left_, right_;
};

#endif
