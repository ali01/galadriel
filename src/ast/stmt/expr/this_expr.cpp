#include "this_expr.h"

/* project includes */
#include <scope/scope.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/decl includes */
#include "../../decl/object/class_decl.h"

/* ast/type includes */
#include "../../type/type.h"

ThisExpr::Ptr
ThisExpr::ThisExprNew(Node::Ptr _parent, Scope::Ptr _scope) {
  struct yyltype loc;
  memset(&loc, 0x0, sizeof loc);
  Ptr ex = new ThisExpr(loc);

  ex->parentIs(_parent);
  ex->scopeIs(_scope);

  return ex;
}

Type::PtrConst
ThisExpr::type() const {
  Type::PtrConst type = Type::kError;
  ClassDecl::PtrConst class_decl = nearestClass();
  if (class_decl)
    type = class_decl->type();

  return type;
}

Location::Ptr
ThisExpr::location() const {
  return Location::LocationNew(Location::kStack, 1, "this");
}
