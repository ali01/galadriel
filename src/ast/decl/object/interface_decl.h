#ifndef INTERFACE_DECL_H_CNDLG689
#define INTERFACE_DECL_H_CNDLG689

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast includes */
#include "../decl.h"

/* ast/decl/object includes */
#include "object_decl.h"

/* forward declarations */
class Identifier;

class InterfaceDecl : public ObjectDecl {
public:
  InterfaceDecl(Identifier *name, Deque<Decl*>::Ptr members);
};

#endif
