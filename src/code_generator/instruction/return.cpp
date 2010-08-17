#include "return.h"

/* code_generator includes */
#include "../location_includes.h"

namespace In {

Return::Ptr
Return::ReturnNew(Location::Ptr _ret) {
  return new Return(_ret);
}

Return::Return(Location::Ptr _ret) : ret_loc_(_ret) {}

Location::Ptr
Return::returnLocation() {
  return ret_loc_;
}

Location::Ptr
Return::returnLocation() const {
  return ret_loc_;
}


} /* end of namespace In */
