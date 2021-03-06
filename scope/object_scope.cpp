#include "object_scope.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

ObjectScope::ObjectScope(Scope::Ptr _parent_scope) : Scope(_parent_scope) {
  node_functor_ = NodeFunctor::NodeFunctorNew(this);
}

void
ObjectScope::NodeFunctor::operator()(VarDecl *_d) { // TODO:is this ever called?
  Location::Offset off = scope_->varDeclCount();
  Location::Segment seg = Location::kHeap;

  VarLocation::Ptr loc;
  loc = VarLocation::VarLocationNew(seg, off, _d);
  _d->locationIs(loc);

  /* calling base class version */
  Scope::NodeFunctor::operator()(_d);
}
