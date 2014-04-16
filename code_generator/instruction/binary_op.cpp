#include "binary_op.h"

/* code_generator includes */
#include "../location_includes.h"

namespace In {

BinaryOp::Ptr
BinaryOp::BinaryOpNew(OpCode _op, Location::Ptr _dst,
                                  Location::Ptr _lhs,
                                  Location::Ptr _rhs) {
  return new BinaryOp(_op, _dst, _lhs, _rhs);
}

BinaryOp::BinaryOp(OpCode _op, Location::Ptr _dst,
                               Location::Ptr _lhs,
                               Location::Ptr _rhs) :
  op_code_(_op), dst_(_dst), lhs_(_lhs), rhs_(_rhs)
{
  assert(dst_ && lhs_ && rhs_);
}

string
BinaryOp::op_str() const {
  switch (op_code_) {
    case kAdd:      return "+";
    case kSubtract: return "-";
    case kMultiply: return "*";
    case kDivide:   return "/";
    case kModulo:   return "%";
    case kEqual:    return "==";
    case kLess:     return "<";
    case kAnd:      return "&&";
    case kOr:       return "||";
  }

  return "(unknown operator)";
}

Location::Ptr
BinaryOp::dst() {
  return dst_;
}

Location::Ptr
BinaryOp::dst() const {
  return dst_;
}


Location::Ptr
BinaryOp::lhs() {
  return lhs_;
}

Location::Ptr
BinaryOp::lhs() const {
  return lhs_;
}


Location::Ptr
BinaryOp::rhs() {
  return rhs_;
}

Location::Ptr
BinaryOp::rhs() const {
  return rhs_;
}

} /* end of namespace In */
