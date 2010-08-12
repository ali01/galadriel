#ifndef POP_PARAMS_H_BF5HIWTD
#define POP_PARAMS_H_BF5HIWTD

/* local includes */
#include "instruction.h"

namespace In {

class PopParams : public Instruction {
public:
  typedef Simone::Ptr<const PopParams> PtrConst;
  typedef Simone::Ptr<PopParams> Ptr;

  static Ptr PopParamsNew(int _bytes) {
    return new PopParams(_bytes);
  }

  /* attribute member functions */
  int bytes() const { return bytes_; }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  PopParams(int _bytes) : bytes_(_bytes) {}

  /* data members */
  int bytes_;

  /* operations disallowed */
  PopParams(const PopParams&);
  void operator=(const PopParams&);
};


} /* end of namespace In */

#endif
