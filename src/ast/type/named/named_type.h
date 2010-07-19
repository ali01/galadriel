#ifndef NAMED_TYPE_H_895QHUPL
#define NAMED_TYPE_H_895QHUPL

/* ast/type includes */
#include "../type.h"

/* forward declarations */
class Identifier;
class ObjectDecl;

class NamedType : public Type  {
protected:
  NamedType(Identifier *i);

  /* data members */
  Identifier *id;
};

#endif
