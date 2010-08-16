#include "load_str_const.h"

#include "../location/location.h"

namespace In {

LoadStrConst::Ptr
LoadStrConst::LoadStrConstNew(Simone::Ptr<Location> _dst,
                              const string& _value) {
  return new LoadStrConst(_dst, _value);
}

LoadStrConst::LoadStrConst(Simone::Ptr<Location> _dst,
                           const string& _value) :
  dst_(_dst), value_(_value)
{
  assert(dst_);
  if (value_.length() > kMaxStringLength)
    value_ = value_.substr(0, kMaxStringLength) + "...";
}

Location::Ptr
LoadStrConst::dst() {
  return dst_;
}

Location::PtrConst
LoadStrConst::dst() const {
  return dst_;
}

} /* end of namespace In */
