#ifndef DOUBLE_CONSTANT_H_CG464C3B
#define DOUBLE_CONSTANT_H_CG464C3B

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class DblConstExpr : public SingleAddrExpr {
public:
  DblConstExpr(yyltype loc, double v) : SingleAddrExpr(loc) { value = v; }

protected:
  /* data members */
  double value;
};

#endif
