#include "begin_func.h"

/* stl includes */
#include <limits>

/* local includes */
#include "label.h"

const BeginFunc::FrameSize BeginFunc::kInvalidFrameSize =
  std::numeric_limits<BeginFunc::FrameSize>::max();

BeginFunc::Ptr
BeginFunc::BeginFuncNew(Label::Ptr _label, FrameSize _size) {
  return new BeginFunc(_label, _size);
}

BeginFunc::BeginFunc(Label::Ptr _label, FrameSize _size) :
  label_(_label), frame_size_(_size)
{
  assert(label_ != NULL);
}

Label::Ptr
BeginFunc::label() {
  return label_;
}

Label::PtrConst
BeginFunc::label() const {
  return label_;
}
