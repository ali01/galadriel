#include "store.h"

/* code_generator includes */
#include "../location/location.h"

namespace In {

Store::Ptr
Store::StoreNew(Location::Ptr _src, Location::Ptr _dst) {
  return new Store(_src, _dst);
}

Store::Store(Location::Ptr _src, Location::Ptr _dst) :
  src_(_src), dst_(_dst)
{
  assert(src_ && dst_);
}

Location::Ptr
Store::src() {
  return src_;
}

Location::PtrConst
Store::src() const {
  return src_;
}

Location::Ptr
Store::dst() {
  return dst_;
}

Location::PtrConst
Store::dst() const {
  return dst_;
}

} /* end of namespace In */