#include "named_type.h"

/* simone includes */
#include <simone/utility.h>

/* ast includes */
#include "../identifier.h"

NamedType::NamedType(Identifier::Ptr _id) :
  Type(*_id->lexLoc(), _id->name()), id_(_id)
{
  assert(id_ != NULL);
  eq_functor_ = NamedTypeEqualityFunctor::NamedTypeEqualityFunctorNew(this);
}

Identifier::Ptr
NamedType::identifier() const {
  return id_;
}

NamedType::NamedTypeEqualityFunctor::NamedTypeEqualityFunctor(NamedType::Ptr t):
  TypeEqualityFunctor(t) {}

void
NamedType::NamedTypeEqualityFunctor::operator()(NamedType *_o) {
  NamedType::PtrConst nt = Ptr::st_cast<const NamedType>(type_);
  equal_ = *nt->identifier() == *_o->identifier();
}
