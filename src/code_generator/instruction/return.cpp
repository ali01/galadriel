#include "return.h"

/* code_generator includes */
#include "../location/location.h"

namespace In {

Return::Ptr
Return::ReturnNew(Location::PtrConst _ret) {
  return new Return(_ret);
}

Return::Return(Location::PtrConst _ret) : ret_loc_(_ret) {}

Location::PtrConst
Return::returnLocation() {
  return ret_loc_;
}

Location::PtrConst
Return::returnLocation() const {
  return ret_loc_;
}


} /* end of namespace In */
