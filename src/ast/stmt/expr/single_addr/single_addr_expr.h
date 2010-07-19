#ifndef SINGLE_ADDR_EXPR_H_9A4HG6MH
#define SINGLE_ADDR_EXPR_H_9A4HG6MH

/* project includes */
#include <lex_loc.h>

/* expr includes */
#include "../expr.h"

class SingleAddrExpr : public Expr {
public:
  SingleAddrExpr(yyltype loc) : Expr(loc) {}
};

#endif
