#include "goto.h"

/* local includes */
#include "label.h"

namespace In {

Goto::Ptr
Goto::GotoNew(Label::Ptr _label) {
  return new Goto(_label);
}

Goto::Goto(Label::Ptr _label) : label_(_label) {
  assert(label_);
}

Label::Ptr
Goto::label() {
  return label_;
}

Label::PtrConst
Goto::label() const {
  return label_;
}

} /* end of namespace In */
