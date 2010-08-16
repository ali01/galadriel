#include "load_int_const.h"

/* code_generator includes */
#include "../location/location.h"

namespace In {

LoadIntConst::Ptr
LoadIntConst::LoadIntConstNew(Location::PtrConst _loc, int _val) {
  return new LoadIntConst(_loc, _val);
}

LoadIntConst::LoadIntConst(Location::PtrConst _loc, int _val) :
                           dst_(_loc), value_(_val) {
  assert(dst_ != NULL);
}

Location::PtrConst
LoadIntConst::dst() {
  return dst_;
}

Location::PtrConst
LoadIntConst::dst() const {
  return dst_;
}

} /* end of namespace In */
