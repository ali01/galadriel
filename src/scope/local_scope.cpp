#include "local_scope.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

LocalScope::LocalScope(Scope::Ptr _parent_scope) :
  Scope(_parent_scope), temps_(0), var_decls_finalized_(false)
{
  assert(_parent_scope);
  node_functor_ = NodeFunctor::NodeFunctorNew(this);
}

TmpLocation::PtrConst
LocalScope::tempNew() {
  var_decls_finalized_ = true;
  Location::Offset off = kLocalsOffset - this->size();
  ++temps_;

  return TmpLocation::TmpLocationNew(off);;
}

size_t
LocalScope::size(bool include_parents) const {
  size_t size;

  Scope::PtrConst parent_scope = parentScope();
  if (include_parents && parent_scope && parent_scope->isLocalScope()) {
    LocalScope::PtrConst parent_scope_local;
    parent_scope_local = Ptr::st_cast<const LocalScope>(parent_scope);
    size = parent_scope_local->size();
  } else {
    size = this->varDeclCount() + temps_;

    LocalScope::Ptr child;
    for (const_child_iter it = childrenBegin(); it != childrenEnd(); ++it) {
      child = Ptr::st_cast<LocalScope>(*it);
      size += child->size(false);
    }
  }

  return size;
}

void
LocalScope::NodeFunctor::operator()(VarDecl *_d) {
  LocalScope::Ptr local_scope = Ptr::st_cast<LocalScope>(scope_);
  assert(not local_scope->var_decls_finalized_);

  Location::Offset off = kLocalsOffset - scope_->varDeclCount();
  Location::Segment seg = Location::kStack;

  VarLocation::PtrConst loc = VarLocation::VarLocationNew(seg, off, _d);
  _d->locationIs(loc);

  /* calling base class version */
  Scope::NodeFunctor::operator()(_d);
}
