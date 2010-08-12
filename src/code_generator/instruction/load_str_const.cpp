#include "load_str_const.h"

#include "../location.h"

namespace In {

LoadStrConst::Ptr
LoadStrConst::LoadStrConstNew(Simone::Ptr<Location> _location,
                              const string& _value) {
  return new LoadStrConst(_location, _value);
}

LoadStrConst::LoadStrConst(Simone::Ptr<Location> _location,
                           const string& _value) :
  location_(_location), value_(_value)
{
  assert(location_);
  if (value_.length() > kMaxStringLength)
    value_ = value_.substr(0, kMaxStringLength) + "...";
}

Location::Ptr
LoadStrConst::location() {
  return location_;
}

Location::PtrConst
LoadStrConst::location() const {
  return location_;
}

} /* end of namespace In */
