#ifndef INTERFACE_TYPE_H_HX1O45LR
#define INTERFACE_TYPE_H_HX1O45LR

/* ast/type/named includes */
#include "named_type.h"

/* forward declarations */
class Identifier;

class InterfaceType : public NamedType {
private:
  /* operations disallowed */
  InterfaceType(Identifier *i) : NamedType(i) {}
};


#endif
