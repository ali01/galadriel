#include "this_expr.h"

/* ast/decl includes */
#include "../../../../decl/class_decl.h"

/* ast/type includes */
#include "../../../../type/type.h"

Type::PtrConst
ThisExpr::type() const {
  Type::PtrConst type = Type::kError;
  ClassDecl::PtrConst class_decl = enclosingClass();
  if (class_decl)
    type = class_decl->type();

  return type;
}