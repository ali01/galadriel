#ifndef ERROR_TYPE_H_UR69VJQM
#define ERROR_TYPE_H_UR69VJQM

/* project includes */
#include <lex_loc.h>

/* ast/type includes */
#include "type.h"

#define kErrorType ErrorType::errorType

class ErrorType : public Type {
public:
  static ErrorType *errorType;

  ErrorType(yyltype loc) : Type(loc) {}
  ErrorType(const char *str) : Type(str) {}
};

#endif
