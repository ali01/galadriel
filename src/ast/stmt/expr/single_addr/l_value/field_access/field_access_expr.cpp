#include "field_access_expr.h"

/* simone includes */
#include <simone/utility.h>

/* ast includes */
#include "../../../../../identifier.h"

/* ast/decl includes */
#include "../../../../../decl/var_decl.h"

/* ast/decl/object includes */
#include "../../../../../decl/object/class_decl.h"

/* ast/type/named includes */
#include "../../../../../type/named/named_type.h"

/* ast/stmt/expr includes */
#include "../../../expr.h"

/* ast/stmt/expr/single_addr/l_value includes */
#include "../l_value_expr.h"


FieldAccessExpr::FieldAccessExpr(yyltype loc) :
  LValueExpr(loc), base_(NULL), field_(NULL), field_type_(NULL) {}


FieldAccessExpr::FieldAccessExpr(Expr *b, Identifier *f) :
  LValueExpr(b ?  Join(b->lexLoc(), f->lexLoc()) : *f->lexLoc()),
  base_(b), field_(f), field_type_(NULL)
{
  /* b can be null (just means no explicit base) */
  assert(field_);
}
