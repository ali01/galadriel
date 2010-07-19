#ifndef OPERATOR_H_CWOPLH8P
#define OPERATOR_H_CWOPLH8P

/* stl includes */
#include <ostream>
using std::ostream;


/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "node.h"

class Operator : public Node {
public:
  Operator(yyltype loc, const char *tok);

  friend ostream& operator<<(ostream& out, Operator *o) {
    return out << o->_tokenString;
  }

protected:
  char _tokenString[4];
};

#endif
