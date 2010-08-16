#include "store.h"

/* code_generator includes */
#include "../location_includes.h"

namespace In {

Store::Ptr
Store::StoreNew(Location::PtrConst _src, Location::PtrConst _dst) {
  return new Store(_src, _dst);
}

Store::Store(Location::PtrConst _src, Location::PtrConst _dst) :
  src_(_src), dst_(_dst)
{
  assert(src_ && dst_);
}

Location::PtrConst
Store::src() {
  return src_;
}

Location::PtrConst
Store::src() const {
  return src_;
}

Location::PtrConst
Store::dst() {
  return dst_;
}

Location::PtrConst
Store::dst() const {
  return dst_;
}

} /* end of namespace In */