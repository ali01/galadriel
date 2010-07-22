#include "array_access_expr.h"

/* ast/stmt/expr includes */
#include "../../expr.h"

ArrayAccessExpr::ArrayAccessExpr(yyltype loc, Expr::Ptr b, Expr::Ptr s) :
  LValueExpr(loc), base(b), subscript(s) {}
