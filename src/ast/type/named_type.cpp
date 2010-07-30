#include "named_type.h"

/* simone includes */
#include <simone/utility.h>

/* ast includes */
#include "../identifier.h"

NamedType::NamedType(Identifier::Ptr i) :
  Type(*i->lexLoc(), i->name()), id_(i)
{
  assert(id_);
}

Simone::Ptr<Identifier>
NamedType::identifier() const {
  return id_;
}