#include "interface_decl.h"

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

InterfaceDecl::InterfaceDecl(Identifier *n, Deque<Decl*>::Ptr m) :
  ObjectDecl(n, m) {}