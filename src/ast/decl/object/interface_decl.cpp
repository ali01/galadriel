#include "interface_decl.h"

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include "../../identifier.h"

InterfaceDecl::InterfaceDecl(Identifier::Ptr name,
                             Deque<Decl::Ptr>::Ptr members) :
  ObjectDecl(name, members) {}
