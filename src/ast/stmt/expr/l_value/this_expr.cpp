#include "this_expr.h"

/* code_generator includes */
#include <code_generator/location/location.h>

/* ast/decl includes */
#include "../../../decl/object/class_decl.h"

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
ThisExpr::type() const {
  Type::PtrConst type = Type::kError;
  ClassDecl::PtrConst class_decl = nearestClass();
  if (class_decl)
    type = class_decl->type();

  return type;
}

Location::Ptr
ThisExpr::location() {
  return NULL;
}