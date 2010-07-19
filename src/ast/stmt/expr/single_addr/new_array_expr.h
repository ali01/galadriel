#ifndef NEW_ARRAY_EXPR_H_MSJQ9O4H
#define NEW_ARRAY_EXPR_H_MSJQ9O4H

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Expr;
class NamedType;
class Type;

class NewArrayExpr : public SingleAddrExpr {
public:
  NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);

private:
  /* data members */
  Expr *size_;
  Type *elem_type_;
};

#endif
