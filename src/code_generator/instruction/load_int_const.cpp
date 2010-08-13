#include "load_int_const.h"

/* code_generator includes */
#include "../location.h"

namespace In {

LoadIntConst::Ptr
LoadIntConst::LoadIntConstNew(Location::Ptr _loc, int _val) {
  return new LoadIntConst(_loc, _val);
}

LoadIntConst::LoadIntConst(Location::Ptr _loc, int _val) :
                           dst_(_loc), value_(_val) {
  assert(dst_ != NULL);
}

Location::Ptr
LoadIntConst::dst() {
  return dst_;
}

Location::PtrConst
LoadIntConst::dst() const {
  return dst_;
}

} /* end of namespace In */
