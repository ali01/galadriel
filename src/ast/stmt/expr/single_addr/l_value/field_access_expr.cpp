#include "field_access_expr.h"

/* simone includes */
#include <simone/utility.h>

/* ast includes */
#include "../../../../identifier.h"

/* ast/decl includes */
#include "../../../../decl/var_decl.h"

/* ast/decl/object includes */
#include "../../../../decl/class_decl.h"

/* ast/type/named includes */
#include "../../../../type/named_type.h"

/* ast/stmt/expr includes */
#include "../../expr.h"

/* ast/stmt/expr/single_addr/l_value includes */
#include "l_value_expr.h"


FieldAccessExpr::FieldAccessExpr(Expr::Ptr b, Identifier::Ptr f) :
  LValueExpr(b != NULL ?  Join(b->lexLoc(), f->lexLoc()) : *f->lexLoc()),
  base_(b), field_(f)
{
  /* b can be null (just means no explicit base) */
  assert(field_ != NULL);
}

Identifier::Ptr
FieldAccessExpr::field() {
  return field_;
}

Identifier::PtrConst
FieldAccessExpr::field() const {
  return field_;
}

Type::PtrConst
FieldAccessExpr::type() const {
  // TODO:
  assert(false);
  return NULL;
}
