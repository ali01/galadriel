#include "assign.h"

/* code_generator includes */
#include "../location_includes.h"

namespace In {

Assign::Ptr
Assign::AssignNew(Location::Ptr _src, Location::Ptr _dst) {
  return new Assign(_src, _dst);
}

Assign::Assign(Location::Ptr _src, Location::Ptr _dst) :
  src_(_src), dst_(_dst)
{
  assert(src_ && dst_);
}

Location::Ptr
Assign::src() {
  return src_;
}

Location::Ptr
Assign::src() const {
  return src_;
}

Location::Ptr
Assign::dst() {
  return dst_;
}

Location::Ptr
Assign::dst() const {
  return dst_;
}

} /* end of namespace In */
