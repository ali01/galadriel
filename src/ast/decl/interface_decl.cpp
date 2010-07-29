#include "interface_decl.h"

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include <local_scope.h>

/* ast includes */
#include "../identifier.h"

InterfaceDecl::InterfaceDecl(Identifier::Ptr _name,
                             Deque<FnDecl::Ptr>::Ptr _members) :
  Decl(_name), members_(_members)
{
  local_scope_ = LocalScope::LocalScopeNew();
}
