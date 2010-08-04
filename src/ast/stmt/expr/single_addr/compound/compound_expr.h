#ifndef COMPOUND_EXPR_H_9BBM4SJA
#define COMPOUND_EXPR_H_9BBM4SJA

/* simone includes */
#include <simone/ptr_interface.h>

// TODO: think about where operator.h belongs
/* ast includes */
#include "../../../../operator.h"

/* single-addr includes */
#include "../single_addr_expr.h"


class CompoundExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const CompoundExpr> PtrConst;
  typedef Simone::Ptr<CompoundExpr> Ptr;

protected:
  /* binary compound expression */
  CompoundExpr(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs);

  /* unary compound expression */
  CompoundExpr(Operator::Ptr op, Expr::Ptr rhs);

  /* data members */
  Operator::Ptr op;
  Expr::Ptr left, right; /* left will be NULL if unary */
};

#endif
