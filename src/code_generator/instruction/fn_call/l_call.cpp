#include "l_call.h"

/* code_generator/instruction includes */
#include "../label.h"

/* code_generator includes */
#include "../../location_includes.h"

namespace In {

LCall::Ptr
LCall::LCallNew(Label::PtrConst _label, Location::PtrConst _return_loc) {
  return new LCall(_label, _return_loc);
}

LCall::LCall(Label::PtrConst _label, Location::PtrConst _return_loc) :
  FnCall(_return_loc), label_(_label)
{
  assert(_label != NULL);
}

Label::PtrConst
LCall::label() const {
  return label_;
}

} /* end of namespace In */
