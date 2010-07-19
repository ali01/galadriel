#ifndef ARRAY_ACCESS_H_M0ABFQJ4
#define ARRAY_ACCESS_H_M0ABFQJ4

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr/l_value includes */
#include "l_value_expr.h"

/* forward declarations */
class Expr;

class ArrayAccessExpr : public LValueExpr {
public:
  ArrayAccessExpr(yyltype loc, Expr *base, Expr *subscript);

protected:
  Expr *base, *subscript;
};

#endif
