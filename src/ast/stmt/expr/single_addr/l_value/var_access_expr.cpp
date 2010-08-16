#include "var_access_expr.h"

/* code_generator includes */
#include <code_generator/location/location.h>

/* project includes */
#include <scope/scope.h>

/* ast includes */
#include "../../../../identifier.h"

VarAccessExpr::VarAccessExpr(Identifier::Ptr _id) : 
  LValueExpr(*_id->lexLoc()), identifier_(_id)
{
  assert(_id != NULL);
}

Identifier::PtrConst
VarAccessExpr::identifier() const {
  return identifier_;
}

Identifier::Ptr
VarAccessExpr::identifier() {
  return identifier_;
}

VarDecl::PtrConst
VarAccessExpr::varDecl() const {
  Scope::PtrConst scope = this->scope();
  return scope->varDecl(identifier_);
}

Type::PtrConst
VarAccessExpr::type() const {
  Type::PtrConst type = Type::kError;

  VarDecl::PtrConst var_decl = this->varDecl();
  if (var_decl != NULL) {
    type = var_decl->type();
  }

  return type;
}

Location::Ptr
VarAccessExpr::location() {
  return NULL;
}
