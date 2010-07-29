#include "scope.h"

/* project includes */
#include "error.h"

Scope::Scope(const Scope::Ptr& _scope) {
  /* copy constructor deliberately does not copy local_scope */
  if (_scope != NULL) {
    Identifier::PtrConst id;
    Decl::PtrConst decl;

    Scope::const_decl_iter it = _scope->declsBegin();
    for (; it != _scope->declsEnd(); ++it) {
      id = it->first;
      decl = it->second;

      scope_[id] = decl;
    }
  }
}

Decl::PtrConst
Scope::decl(Identifier::PtrConst _id) const {
  Decl::PtrConst decl = NULL;

  const_decl_iter it = scope_.element(_id);
  if (it != scope_.end())
    decl = it->second;

  return decl;
}

void
Scope::declIs(Decl::PtrConst _decl) {
  Identifier::PtrConst id = _decl->identifier();
  const_decl_iter it = local_scope_.element(id);
  if (it == local_scope_.end()) {
    scope_[id] = _decl;
    local_scope_[id] = _decl;
  } else {
    Decl::PtrConst prev_decl = it->second;
    Error::DeclConflict(_decl, prev_decl);
  }
}
