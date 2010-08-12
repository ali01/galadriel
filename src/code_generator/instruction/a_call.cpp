#include "a_call.h"

/* code_generator includes */
#include "../location.h"

namespace In {

ACall::Ptr
ACall::ACallNew(Location::Ptr _fn_loc, Location::Ptr _ret_loc) {
  return new ACall(_fn_loc, _ret_loc);
}

ACall::ACall(Location::Ptr _fn_loc, Location::Ptr _ret_loc) :
  fn_loc_(_fn_loc), ret_loc_(_ret_loc)
{
  assert(fn_loc_);
}

Location::Ptr
ACall::functionLocation() {
  return fn_loc_;
}

Location::PtrConst
ACall::functionLocation() const {
  return fn_loc_;
}

Location::Ptr
ACall::returnLocation() {
  return ret_loc_;
}

Location::PtrConst
ACall::returnLocation() const {
  return ret_loc_;
}


} /* end of namespace In */
