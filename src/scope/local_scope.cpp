#include "local_scope.h"

/* code_generator includes */
#include <code_generator/location/var_location.h>
#include <code_generator/location/tmp_location.h>

LocalScope::LocalScope(Scope::Ptr _parent_scope) :
  Scope(_parent_scope), temps_(0), var_decls_finalized_(false)
{
  assert(_parent_scope);
  node_functor_ = NodeFunctor::NodeFunctorNew(this);
}

TmpLocation::PtrConst
LocalScope::tempNew() {
  var_decls_finalized_ = true;
  Location::Offset off = kLocalsOffset - this->varDeclCount() - temps_;

  TmpLocation::PtrConst loc = TmpLocation::TmpLocationNew(off);
  ++temps_;

  return loc;
}

size_t
LocalScope::frameSize() const {
  return this->varDeclCount() + temps_;
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
