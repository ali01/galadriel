#include "scope.h"

Scope::Scope(const Scope::Ptr& _scope) {
  if (_scope != NULL) {
    Decl::PtrConst decl;
    Scope::const_decl_iter it = _scope->begin();
    for (; it != _scope->end(); ++it) {
      decl = it->second;
      this->declIs(decl);
    }
  }
}

Decl::PtrConst
Scope::decl(Identifier::PtrConst _id) const {
  Decl::PtrConst decl = NULL;

  const_decl_iter it = decl_map_.element(_id);
  if (it != decl_map_.end())
    decl = it->second;

  return decl;
}

void
Scope::declIs(Decl::PtrConst _decl) {
  Identifier::PtrConst id = _decl->identifier();
  decl_map_.elementIs(id, _decl);
}
