#include "named_type.h"

/* simone includes */
#include <simone/utility.h>

/* ast includes */
#include "../../identifier.h"

NamedType::NamedType(Identifier *i) :
  Type(*i->lexLoc(), i->name()), id(i)
{
  assert(id);
}
