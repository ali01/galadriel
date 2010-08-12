#ifndef LOAD_CONST_H_MQ27Z88Q
#define LOAD_CONST_H_MQ27Z88Q

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;

namespace In {

class LoadIntConst : public Instruction {
public:
  typedef Simone::Ptr<const LoadIntConst> PtrConst;
  typedef Simone::Ptr<LoadIntConst> Ptr;

  static Ptr LoadIntConstNew(Simone::Ptr<const Location> _loc, int _val);

  /* attribute member functions */
  Simone::Ptr<const Location> location() const;
  int value() const { return value_; }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  LoadIntConst(Simone::Ptr<const Location> _loc, int _val);

  /* data members */
  Simone::Ptr<const Location> location_;
  int value_;

  /* disallowed operations */
  LoadIntConst(const LoadIntConst&);
  void operator=(const LoadIntConst&);
};

} /* end of namespace In */

#endif
