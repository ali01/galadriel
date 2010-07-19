#ifndef READ_INTEGER_EXPR_H_DZTNBZO5
#define READ_INTEGER_EXPR_H_DZTNBZO5

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class ReadIntegerExpr : public SingleAddrExpr {
public:
  ReadIntegerExpr(yyltype loc) : SingleAddrExpr(loc) {}
};


#endif
