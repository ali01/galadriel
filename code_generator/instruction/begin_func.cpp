#include "begin_func.h"

/* stl includes */
#include <limits>

/* local includes */
#include "label.h"

namespace In {

const BeginFunc::FrameSize BeginFunc::kInvalidFrameSize =
  std::numeric_limits<BeginFunc::FrameSize>::max();

BeginFunc::Ptr
BeginFunc::BeginFuncNew(Label::Ptr _label) {
  return new BeginFunc(_label);
}

BeginFunc::BeginFunc(Label::Ptr _label) :
  label_(_label), frame_size_(kInvalidFrameSize)
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

} /* end of namespace In */
