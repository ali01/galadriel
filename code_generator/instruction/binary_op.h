#ifndef BINARY_OP_H_6KQU47AP
#define BINARY_OP_H_6KQU47AP

/* stl includes */
#include <string>
using std::string;

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;

namespace In {

class BinaryOp : public Instruction {
public:
  typedef Simone::Ptr<const BinaryOp> PtrConst;
  typedef Simone::Ptr<BinaryOp> Ptr;

  enum OpCode {
    /* arithmetic */
    kAdd, kSubtract, kMultiply, kDivide, kModulo,

    /* relational */
    kEqual, kLess,

    /* logical */
    kAnd, kOr
  };

  static Ptr BinaryOpNew(OpCode _op, Simone::Ptr<Location> _dst,
                                     Simone::Ptr<Location> _lhs,
                                     Simone::Ptr<Location> _rhs);

  /* attribute member functions */
  string op_str() const;
  OpCode op_code() const { return op_code_; }

  Simone::Ptr<Location> dst();
  Simone::Ptr<Location> dst() const;

  Simone::Ptr<Location> lhs();
  Simone::Ptr<Location> lhs() const;

  Simone::Ptr<Location> rhs();
  Simone::Ptr<Location> rhs() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  BinaryOp(OpCode _op, Simone::Ptr<Location> _dst,
                       Simone::Ptr<Location> _lhs,
                       Simone::Ptr<Location> _rhs);

  /* data members */
  OpCode op_code_;
  Simone::Ptr<Location> dst_, lhs_, rhs_;

  /* operations disallowed */
  BinaryOp(const BinaryOp&);
  void operator=(const BinaryOp&);
};

} /* end of namespace In */


#endif
