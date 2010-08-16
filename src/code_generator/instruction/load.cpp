#include "load.h"

/* code_generator includes */
#include "../location/location.h"

namespace In {

Load::Ptr
Load::LoadNew(Location::PtrConst _src, Location::PtrConst _dst) {
  return new Load(_src, _dst);
}

Load::Load(Location::PtrConst _src, Location::PtrConst _dst) : 
  src_(_src), dst_(_dst)
{
  assert(src_ && dst_);
}

Location::PtrConst
Load::src() {
  return src_;
}

Location::PtrConst
Load::src() const {
  return src_;
}

Location::PtrConst
Load::dst() {
  return dst_;
}

Location::PtrConst
Load::dst() const {
  return dst_;
}

} /* end of namespace In */
