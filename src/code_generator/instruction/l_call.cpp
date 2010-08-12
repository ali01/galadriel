#include "l_call.h"

/* local includes */
#include "label.h"

/* code_generator includes */
#include "../location.h"

namespace In {

LCall::Ptr
LCall::LCallNew(Label::Ptr _label, Location::Ptr _return_loc) {
  return new LCall(_label, _return_loc);
}

LCall::LCall(Label::Ptr _label, Location::Ptr _return_loc) :
  label_(_label), return_loc_(_return_loc)
{
  assert(_label != NULL);
}

Label::Ptr
LCall::label() {
  return label_;
}

Label::PtrConst
LCall::label() const {
  return label_;
}

Location::Ptr
LCall::returnLocation() {
  return return_loc_;
}

Location::PtrConst
LCall::returnLocation() const {
  return return_loc_;
}

} /* end of namespace In */
