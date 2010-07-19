#ifndef STRING_CONSTANT_H_5V21HZS6
#define STRING_CONSTANT_H_5V21HZS6

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class StrConstExpr : public SingleAddrExpr {
public:
  StrConstExpr(yyltype loc, const char *v);

protected:
  /* data members */
  char *value;
};

#endif
