#include "push_param.h"

/* code_generator includes */
#include "../location/location.h"

namespace In {

PushParam::Ptr
PushParam::PushParamNew(Location::PtrConst _param_loc) {
  return new PushParam(_param_loc);
}

PushParam::PushParam(Location::PtrConst _loc) : param_loc_(_loc) {
  assert(param_loc_);
}

Location::PtrConst
PushParam::paramLocation() {
  return param_loc_;
}

Location::PtrConst
PushParam::paramLocation() const {
  return param_loc_;
}

} /* end of namespace In */
