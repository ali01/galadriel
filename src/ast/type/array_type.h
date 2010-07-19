#ifndef ARRAY_TYPE_H_J35FQYOQ
#define ARRAY_TYPE_H_J35FQYOQ

/* project includes */
#include <lex_loc.h>

/* ast/type includes */
#include "type.h"

class ArrayType : public Type {
public:
  ArrayType(yyltype loc, Type *elemType);

protected:
  /* data members */
  Type *_elemType;
};

#endif
