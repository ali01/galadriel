#include "class_decl.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* ast/type includes */
#include "../../type/named_type.h"

ClassDecl::ClassDecl(Identifier::Ptr name, NamedType::Ptr extends,
                     Deque<NamedType::Ptr>::Ptr implements,
                     Deque<Decl::Ptr>::Ptr members) :
  ObjectDecl(name, members), extends(extends), implements(implements)
{
  /* extends can be NULL, impl & mem may be empty lists but cannot be NULL */
  /* n & mem are verified by superclass */
  assert(implements);
}
