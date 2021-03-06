#include "a_call.h"

/* code_generator includes */
#include "../../location_includes.h"

namespace In {

ACall::Ptr
ACall::ACallNew(Location::Ptr _fn_loc, Location::Ptr _ret_loc) {
  return new ACall(_fn_loc, _ret_loc);
}

ACall::ACall(Location::Ptr _fn_loc, Location::Ptr _ret_loc) :
  FnCall(_ret_loc), fn_loc_(_fn_loc)
{
  assert(fn_loc_);
}

Location::Ptr
ACall::functionLocation() {
  return fn_loc_;
}

Location::Ptr
ACall::functionLocation() const {
  return fn_loc_;
}

} /* end of namespace In */
