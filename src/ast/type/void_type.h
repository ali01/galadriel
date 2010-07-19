#ifndef VOID_TYPE_H_I8L644J0
#define VOID_TYPE_H_I8L644J0

/* project includes */
#include <lex_loc.h>

/* ast/type includes */
#include "type.h"

#define kVoidType VoidType::voidType

class VoidType : public Type {
public:
  static VoidType *voidType;

  VoidType(yyltype loc) : Type(loc) {}
  VoidType(const char *str) : Type(str) {}
};

#endif
