#ifndef L_VALUE_H_YX6Y3KF6
#define L_VALUE_H_YX6Y3KF6

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/singl_addr includes */
#include "../single_addr_expr.h"

class LValueExpr : public SingleAddrExpr {
public:
  LValueExpr(yyltype loc) : SingleAddrExpr(loc) {}
};

#endif
