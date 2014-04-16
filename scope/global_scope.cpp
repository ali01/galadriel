#include "global_scope.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

GlobalScope::GlobalScope() : Scope(NULL) {
  node_functor_ = NodeFunctor::NodeFunctorNew(this);
}

void
GlobalScope::NodeFunctor::operator()(VarDecl *_d) {
  Location::Offset off = scope_->varDeclCount();
  Location::Segment seg = Location::kData;

  VarLocation::Ptr loc;
  loc = VarLocation::VarLocationNew(seg, off, _d);

  _d->locationIs(loc);

  /* calling base class version */
  Scope::NodeFunctor::operator()(_d);
}
