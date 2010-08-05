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
#include <lex_loc.h>

/* ast includes */
#include "node.h"

class Operator : public Node {
public:
  typedef Simone::Ptr<const Operator> PtrConst;
  typedef Simone::Ptr<Operator> Ptr;

  enum op_type {
    kAdd, kSubtract, kMultiply, kDivide, kModulo, kEqual, kNotEqual,
    kLess, kLessEqual, kGreater, kGreaterEqual,
    kAnd, kOr, kNot
  };

  static Ptr OperatorNew(yyltype loc, op_type _op_type) {
    return new Operator(loc, _op_type);
  }

  Operator(yyltype loc, op_type _op_type);

  op_type operatorType() const { return op_type_; }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  const op_type op_type_;
};

#endif
