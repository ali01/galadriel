#ifndef COMPOUND_EXPR_H_9BBM4SJA
#define COMPOUND_EXPR_H_9BBM4SJA

/* simone includes */
#include <simone/ptr_interface.h>

/* single-addr includes */
#include "../single_addr_expr.h"

/* forward declarations */
class Operator;


class CompoundExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const CompoundExpr> PtrConst;
  typedef Simone::Ptr<CompoundExpr> Ptr;

  /* attribute member functions */
  Expr::Ptr left() { return left_; }
  Expr::PtrConst left() const { return left_; }

  Simone::Ptr<Operator> op();
  Simone::Ptr<const Operator> op() const;

  Expr::Ptr right() { return right_; }
  Expr::PtrConst right() const { return right_; }

protected:
  /* binary compound expression */
  CompoundExpr(Expr::Ptr lhs, Simone::Ptr<Operator> op, Expr::Ptr rhs);

  /* unary compound expression */
  CompoundExpr(Simone::Ptr<Operator> op, Expr::Ptr rhs);

  /* data members */
  Simone::Ptr<Operator> op_;
  Expr::Ptr left_, right_; /* left will be NULL if unary */
};

#endif
