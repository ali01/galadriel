#include "ifz.h"

/* code_generator includes */
#include "../location/location.h"

/* local includes */
#include "label.h"

namespace In {

IfZ::Ptr
IfZ::IfZNew(Location::PtrConst _test, Label::Ptr _label) {
  return new IfZ(_test, _label);
}

IfZ::IfZ(Location::PtrConst _test, Label::Ptr _label) :
  test_(_test), label_(_label)
{
  assert(test_ && label_);
}

Location::PtrConst
IfZ::test() {
  return test_;
}

Location::PtrConst
IfZ::test() const {
  return test_;
}

Label::Ptr
IfZ::label() {
  return label_;
}

Label::PtrConst
IfZ::label() const {
  return label_;
}


} /* end of namespace In */
