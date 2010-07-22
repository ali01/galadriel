#include "object_decl.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* ast/decl includes */
#include "../decl.h"

/* ast/type/named includes */
#include "../../type/named_type.h"

/* forward declarations */
class Identifier;

ObjectDecl::ObjectDecl(Simone::Ptr<Identifier> n, Deque<Decl::Ptr>::Ptr m) :
  Decl(n), members(m)
{
  assert(members); // n verified by superclass
}
