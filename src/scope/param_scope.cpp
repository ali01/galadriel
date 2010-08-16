#include "param_scope.h"

/* code_generator includes */
#include <code_generator/location/var_location.h>

ParamScope::ParamScope(Scope::Ptr _parent_scope) : Scope(_parent_scope) {
  node_functor_ = NodeFunctor::NodeFunctorNew(this);
}

void
ParamScope::NodeFunctor::operator()(VarDecl *_d) {
  Location::Offset off = scope_->varDeclCount() + kParamsOffset;
  Location::Segment seg = Location::kStack;

  VarLocation::PtrConst loc;
  loc = VarLocation::VarLocationNew(seg, off, _d);

  _d->locationIs(loc);

  /* calling base class version */
  Scope::NodeFunctor::operator()(_d);
}
