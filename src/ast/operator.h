#ifndef OPERATOR_H_CWOPLH8P
#define OPERATOR_H_CWOPLH8P

/* stl includes */
#include <ostream>
using std::ostream;

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "node.h"

class Operator : public Node {
public:
  typedef Simone::Ptr<const Operator> PtrConst;
  typedef Simone::Ptr<Operator> Ptr;

  static Ptr OperatorNew(yyltype loc, const char *tok) {
    return new Operator(loc, tok);
  }

  Operator(yyltype loc, const char *tok);

  friend ostream& operator<<(ostream& out, Operator *o) {
    return out << o->_tokenString;
  }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

protected:
  char _tokenString[4];
};

#endif
