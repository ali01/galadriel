#ifndef INT_CONSTANT_H_BNDXZ4HE
#define INT_CONSTANT_H_BNDXZ4HE

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class IntConstExpr : public SingleAddrExpr {
public:
  IntConstExpr(yyltype loc, int val) : SingleAddrExpr(loc) { value = val; }

private:
  /* data members */
  int value;
};

#endif
