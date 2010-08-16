#include "var_decl.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast includes */
#include "../identifier.h"

/* ast/type includes */
#include "../type/type.h"

VarDecl::Ptr
VarDecl::VarDeclNew(Identifier::Ptr name, Type::Ptr type) {
  return new VarDecl(name, type);
}

VarDecl::VarDecl(Identifier::Ptr n, Type::Ptr t) : Decl(n), type_(t) {
  assert(n != NULL && t != NULL);
}

Type::Ptr
VarDecl::type() const {
  return type_;
}

VarLocation::PtrConst
VarDecl::location() const {
  return location_;
}

void
VarDecl::locationIs(VarLocation::PtrConst _loc) {
  location_ = _loc;
}
