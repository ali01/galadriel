#include "load_label.h"

/* code_generator includes */
#include "../location/location.h"

/* local includes */
#include "label.h"

namespace In {

LoadLabel::Ptr
LoadLabel::LoadLabelNew(Location::PtrConst _loc, Label::Ptr _label) {
  return new LoadLabel(_loc, _label);
}

LoadLabel::LoadLabel(Location::PtrConst _loc, Label::Ptr _label) :
  dst_(_loc), label_(_label)
{
  assert(_loc && _label);
}

Location::PtrConst
LoadLabel::dst() {
  return dst_;
}

Location::PtrConst
LoadLabel::dst() const {
  return dst_;
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
