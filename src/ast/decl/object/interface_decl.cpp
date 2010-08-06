#include "interface_decl.h"

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast includes */
#include "../../identifier.h"

InterfaceDecl::InterfaceDecl(Identifier::Ptr _name,
                             Deque<Decl::Ptr>::Ptr _members) :
  ObjectDecl(_name, _members) {}
