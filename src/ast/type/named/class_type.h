#ifndef CLASS_TYPE_H_KPDFAJNS
#define CLASS_TYPE_H_KPDFAJNS

/* ast/type/named includes */
#include "named_type.h"

/* forward declarations */
class Identifier;

class ClassType : public NamedType {
private:
  /* operations disallowed */
  ClassType(Identifier *i) : NamedType(i) {}
};

#endif
