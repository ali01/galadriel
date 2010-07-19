#ifndef NEW_EXPR_H_AVR0MOFS
#define NEW_EXPR_H_AVR0MOFS

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class NamedType;

class NewExpr : public SingleAddrExpr {
public:
  NewExpr(yyltype loc, NamedType *class_type);

private:
  /* data members */
  NamedType *type_;
};


#endif
