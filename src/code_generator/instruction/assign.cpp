#include "assign.h"

/* code_generator includes */
#include "../location_includes.h"

namespace In {

Assign::Ptr
Assign::AssignNew(Location::PtrConst _src, Location::PtrConst _dst) {
  return new Assign(_src, _dst);
}

Assign::Assign(Location::PtrConst _src, Location::PtrConst _dst) :
  src_(_src), dst_(_dst)
{
  assert(src_ && dst_);
}

Location::PtrConst
Assign::src() {
  return src_;
}

Location::PtrConst
Assign::src() const {
  return src_;
}

Location::PtrConst
Assign::dst() {
  return dst_;
}

Location::PtrConst
Assign::dst() const {
  return dst_;
}

} /* end of namespace In */
