#ifndef THIS_H_AWIFBXRQ
#define THIS_H_AWIFBXRQ

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr/l_value/field_access includes */
#include "field_access_expr.h"

// TODO: consider if should inherit from FieldAccessExpr or not
class ThisExpr : public FieldAccessExpr {
public:
  ThisExpr(yyltype loc) : FieldAccessExpr(loc) {}
};

#endif
