#ifndef NULL_EXPR_H_LG6PDF2A
#define NULL_EXPR_H_LG6PDF2A

/* ast/stmt/expr includes */
#include "expr.h"

class NullConstant: public Expr {
public:
  NullConstant(yyltype loc) : Expr(loc) {}
};

#endif
