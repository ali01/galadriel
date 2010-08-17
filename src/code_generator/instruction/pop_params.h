#ifndef POP_PARAMS_H_BF5HIWTD
#define POP_PARAMS_H_BF5HIWTD

/* local includes */
#include "instruction.h"

namespace In {

class PopParams : public Instruction {
public:
  typedef Simone::Ptr<const PopParams> PtrConst;
  typedef Simone::Ptr<PopParams> Ptr;

  static Ptr PopParamsNew(uint32_t _words) {
    return new PopParams(_words);
  }

  /* attribute member functions */
  uint32_t words() const { return words_; }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  PopParams(uint32_t _words) : words_(_words) {}

  /* data members */
  uint32_t words_;

  /* operations disallowed */
  PopParams(const PopParams&);
  void operator=(const PopParams&);
};


} /* end of namespace In */

#endif
