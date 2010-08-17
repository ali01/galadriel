#include "fn_call.h"

/* code_generator includes */
#include "../../location_includes.h"

namespace In {

FnCall::FnCall(Location::Ptr _ret_loc) : ret_loc_(_ret_loc) {}

Location::Ptr
FnCall::returnLocation() {
  return ret_loc_;
}

Location::Ptr
FnCall::returnLocation() const {
  return ret_loc_;
}

} /* end of namespace In */
