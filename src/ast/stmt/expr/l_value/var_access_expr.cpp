#include "var_access_expr.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

/* project includes */
#include <scope/scope.h>

/* ast includes */
#include "../../../identifier.h"

VarAccessExpr::VarAccessExpr(Identifier::Ptr _id) : 
  LValueExpr(*_id->lexLoc()), identifier_(_id)
{
  assert(identifier_);
}

Identifier::Ptr
VarAccessExpr::identifier() {
  return identifier_;
}

Identifier::PtrConst
VarAccessExpr::identifier() const {
  return identifier_;
}

VarDecl::PtrConst
VarAccessExpr::varDecl() const {
  Scope::PtrConst scope = this->scope();
  return scope->varDecl(identifier_);
}

Location::Ptr
VarAccessExpr::location() const {
  Location::Ptr loc = LValueExpr::location();
  if (loc == NULL) {
    VarDecl::PtrConst var_decl = this->varDecl();
    loc = var_decl->location();
  }

  return loc;
}
