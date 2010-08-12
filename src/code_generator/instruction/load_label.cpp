#include "load_label.h"

/* code_generator includes */
#include "../location.h"

/* local includes */
#include "label.h"

namespace In {

LoadLabel::Ptr
LoadLabel::LoadLabelNew(Location::Ptr _loc, Label::Ptr _label) {
  return new LoadLabel(_loc, _label);
}

LoadLabel::LoadLabel(Location::Ptr _loc, Label::Ptr _label) :
  location_(_loc), label_(_label)
{
  assert(_loc && _label);
}

Location::Ptr
LoadLabel::location() {
  return location_;
}

Location::PtrConst
LoadLabel::location() const {
  return location_;
}

Label::Ptr
LoadLabel::label() {
  return label_;
}

Label::PtrConst
LoadLabel::label() const {
  return label_;
}

} /* end of namespace In */
