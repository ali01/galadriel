#ifndef NULL_TYPE_H_KKBRTAXZ
#define NULL_TYPE_H_KKBRTAXZ

/* project includes */
#include <lex_loc.h>

/* ast/type includes */
#include "type.h"

#define kNullType NullType::nullType

class NullType : public Type {
public:
  static NullType *nullType;

  NullType(yyltype loc) : Type(loc) {}
  NullType(const char *str) : Type(str) {}
};


#endif
