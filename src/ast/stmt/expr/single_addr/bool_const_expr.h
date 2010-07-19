#ifndef BOOL_CONSTANT_H_ZCPXRQCL
#define BOOL_CONSTANT_H_ZCPXRQCL

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class BoolConstExpr : public SingleAddrExpr {
public:
  BoolConstExpr(yyltype loc, bool val) : SingleAddrExpr(loc) { value = val; }

protected:
  /* data members */
  bool value;
};


#endif
