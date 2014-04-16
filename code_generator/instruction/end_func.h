#ifndef END_FUNC_H_RZMDU9K1
#define END_FUNC_H_RZMDU9K1

/* local includes */
#include "instruction.h"

namespace In {

class EndFunc : public Instruction {
public:
  typedef Simone::Ptr<const EndFunc> PtrConst;
  typedef Simone::Ptr<EndFunc> Ptr;

  static Ptr EndFuncNew() {
    return new EndFunc();
  }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  EndFunc() {}

  /* operations disallowed */
  EndFunc(const EndFunc&);
  void operator=(const EndFunc&);
};


} /* end of namespace In */

#endif
