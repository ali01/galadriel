#include "push_param.h"

/* code_generator includes */
#include "../location_includes.h"

namespace In {

PushParam::Ptr
PushParam::PushParamNew(Location::Ptr _param_loc) {
  return new PushParam(_param_loc);
}

PushParam::PushParam(Location::Ptr _loc) : param_loc_(_loc) {
  assert(param_loc_);
}

Location::Ptr
PushParam::paramLocation() {
  return param_loc_;
}

Location::Ptr
PushParam::paramLocation() const {
  return param_loc_;
}

} /* end of namespace In */
