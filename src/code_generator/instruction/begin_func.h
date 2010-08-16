#ifndef BEGIN_FUNC_H_PY56AUK2
#define BEGIN_FUNC_H_PY56AUK2

/* local includes */
#include "instruction.h"

namespace In {

/* forward declarations */
class Label;

class BeginFunc : public Instruction {
public:
  typedef Simone::Ptr<const BeginFunc> PtrConst;
  typedef Simone::Ptr<BeginFunc> Ptr;

  typedef size_t FrameSize;

  static const FrameSize kInvalidFrameSize;

  static Ptr BeginFuncNew(Simone::Ptr<Label> _label);

  /* attribute member functions */
  FrameSize frameSize() const { return frame_size_; }
  void frameSizeIs(FrameSize _s) { frame_size_ = _s; }

  Simone::Ptr<Label> label();
  Simone::Ptr<const Label> label() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  BeginFunc(Simone::Ptr<Label> _label);

  Simone::Ptr<Label> label_;
  FrameSize frame_size_;

  /* operations disallowed */
  BeginFunc(const BeginFunc&);
  void operator=(const BeginFunc&);
};

} /* end of namespace In */

#endif
