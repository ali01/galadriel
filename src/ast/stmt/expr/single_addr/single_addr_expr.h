#ifndef SINGLE_ADDR_EXPR_H_9A4HG6MH
#define SINGLE_ADDR_EXPR_H_9A4HG6MH

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* expr includes */
#include "../expr.h"

class SingleAddrExpr : public Expr {
public:
  typedef Simone::Ptr<const SingleAddrExpr> PtrConst;
  typedef Simone::Ptr<SingleAddrExpr> Ptr;

protected:
  SingleAddrExpr(yyltype loc) : Expr(loc) {}
};

#endif
