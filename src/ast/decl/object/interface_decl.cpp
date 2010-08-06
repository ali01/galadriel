#include "interface_decl.h"

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast includes */
#include "../../identifier.h"

InterfaceDecl::InterfaceDecl(Identifier::Ptr _name,
                             Deque<FnDecl::Ptr>::Ptr _members) :
  Decl(_name), members_(_members) {}
