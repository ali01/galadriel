#include "ifz.h"

/* code_generator includes */
#include "../location_includes.h"

/* local includes */
#include "label.h"

namespace In {

IfZ::Ptr
IfZ::IfZNew(Location::Ptr _test, Label::Ptr _label) {
  return new IfZ(_test, _label);
}

IfZ::IfZ(Location::Ptr _test, Label::Ptr _label) :
  test_(_test), label_(_label)
{
  assert(test_ && label_);
}

Location::Ptr
IfZ::test() {
  return test_;
}

Location::Ptr
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
