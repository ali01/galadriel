#ifndef FIELD_ACCESS_H_ZGC2WBOI
#define FIELD_ACCESS_H_ZGC2WBOI

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "../../../../../identifier.h"

/* ast/stmt/expr/single_addr/l_value includes */
#include "../l_value_expr.h"

/* forward declarations */
class Expr;
class Identifier;
class Type;

/* Note that field access is used both for qualified names
 * base.field and just field without qualification. We don't
 * know for sure whether there is an implicit "this." in
 * front until later on, so we use one node type for either
 * and sort it out later. */
class FieldAccessExpr : public LValueExpr {
public:
  FieldAccessExpr(yyltype loc);
  FieldAccessExpr(Expr *base, Identifier *field); //ok to pass NULL base

protected:
  Expr *base_; // will be NULL if no explicit base
  Identifier *field_;
  Type *field_type_;
};

#endif
