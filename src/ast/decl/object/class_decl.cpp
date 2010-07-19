#include "class_decl.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* ast/type/named includes */
#include "../../type/named/class_type.h"
#include "../../type/named/interface_type.h"

ClassDecl::ClassDecl(Identifier *n, ClassType *ex,
                     Deque<InterfaceType*>::Ptr imp, Deque<Decl*>::Ptr m) :
  ObjectDecl(n, m), extends(ex), implements(imp)
{
  /* extends can be NULL, impl & mem may be empty lists but cannot be NULL */
  /* n & mem are verified by superclass */
  assert(implements);
}
