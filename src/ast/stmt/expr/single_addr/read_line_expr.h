#ifndef READ_LINE_EXPR_H_VCPJ04FG
#define READ_LINE_EXPR_H_VCPJ04FG

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class ReadLineExpr : public SingleAddrExpr {
public:
  ReadLineExpr(yyltype loc) : SingleAddrExpr(loc) {}
};

#endif
