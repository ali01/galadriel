#include "l_call.h"

/* code_generator/instruction includes */
#include "../label.h"

/* code_generator includes */
#include "../../location_includes.h"

namespace In {

LCall::Ptr
LCall::LCallNew(Label::Ptr _label, Location::PtrConst _return_loc) {
  return new LCall(_label, _return_loc);
}

LCall::LCall(Label::Ptr _label, Location::PtrConst _return_loc) :
  FnCall(_return_loc), label_(_label)
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

} /* end of namespace In */
