#ifndef OPERATOR_H_CWOPLH8P
#define OPERATOR_H_CWOPLH8P

/* stl includes */
#include <ostream>
#include <string>
using std::ostream;
using std::string;

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast includes */
#include "node.h"

class Operator : public Node {
public:
  typedef Simone::Ptr<const Operator> PtrConst;
  typedef Simone::Ptr<Operator> Ptr;

  enum OpCode {
    /* arithmetic */
    kAdd, kSubtract, kMultiply, kDivide, kModulo,

    /* relational */
    kEqual, kNotEqual, kLess, kLessEqual, kGreater, kGreaterEqual,

    /* logical */
    kAnd, kOr, kNot,

    /* assignment */
    kAssign
  };

  static Ptr OperatorNew(yyltype loc, OpCode _OpCode) {
    return new Operator(loc, _OpCode);
  }

  Operator(yyltype loc, OpCode _OpCode);

  OpCode operatorType() const { return OpCode_; }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  const OpCode OpCode_;
};

/* forward declarations */
ostream& operator<<(ostream& out, const Operator& _op);

#endif
