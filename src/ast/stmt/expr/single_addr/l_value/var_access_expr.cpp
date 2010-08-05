#include "var_access_expr.h"

/* project includes */
#include <scope.h>

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

Type::PtrConst
VarAccessExpr::type() const {
  Type::PtrConst type = Type::kError;
  Scope::PtrConst scope = this->scope();

  VarDecl::PtrConst var_decl = scope->varDecl(identifier_);
  if (var_decl != NULL) {
    type = var_decl->type();
  }

  return type;
}
