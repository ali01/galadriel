#include "class_decl.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* ast/type includes */
#include "../type/named_type.h"

ClassDecl::ClassDecl(Identifier::Ptr name, NamedType::Ptr extends,
                     Deque<NamedType::Ptr>::Ptr implements,
                     Deque<Decl::Ptr>::Ptr members) :
  Decl(name), base_class_(extends), interfaces_(implements), members_(members)
{
  /* extends can be NULL, impl & mem may be empty lists but cannot be NULL */
  assert(interfaces_);
}
