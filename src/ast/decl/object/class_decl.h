#ifndef CLASS_DECL_H_WSH964UZ
#define CLASS_DECL_H_WSH964UZ

/* ast includes */
#include "../../identifier.h"

/* ast/decl includes */
#include "../decl.h"

/* ast/decl/object includes */
#include "object_decl.h"

/* forward declarations */
class ClassType;
class Identifier;
class InterfaceType;

class ClassDecl : public ObjectDecl {
public:
  ClassDecl(Identifier *name, ClassType *extends,
            Deque<InterfaceType*>::Ptr implements, Deque<Decl*>::Ptr members);

  /* data members */
  ClassType *extends;
  Deque<InterfaceType*>::Ptr implements;
};

#endif
