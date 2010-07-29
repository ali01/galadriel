#include "local_scope.h"

#include "error.h"

/* override base class version to disallow replacement */
void
LocalScope::declIs(Decl::PtrConst _decl) {
  Identifier::PtrConst id = _decl->identifier();
  const_decl_iter it = decl_map_.element(id);
  if (it != decl_map_.end()) {
    Decl::PtrConst prev_decl = it->second;
    Error::DeclConflict(_decl, prev_decl);
  } else {
    decl_map_[id] = _decl;
  }
}
