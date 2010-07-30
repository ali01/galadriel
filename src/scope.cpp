#include "scope.h"

/* project includes */
#include "error.h"

Scope::Scope(Scope::PtrConst _parent_scope) : parent_scope_(_parent_scope) {}

Decl::PtrConst
Scope::decl(Identifier::PtrConst _id) const {
  Decl::PtrConst decl = NULL;

  const_decl_iter it = scope_.element(_id);
  if (it != scope_.end())
    decl = it->second;

  if (decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->decl(_id);

  return decl;
}

void
Scope::declIs(Decl::PtrConst _decl) {
  Identifier::PtrConst id = _decl->identifier();
  const_decl_iter it = scope_.element(id);
  if (it == scope_.end()) {
    scope_[id] = _decl;
  } else {
    Decl::PtrConst prev_decl = it->second;
    Error::DeclConflict(_decl, prev_decl);
  }
}
