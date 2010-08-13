#ifndef LOAD_H_DVXHXZ1T
#define LOAD_H_DVXHXZ1T

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;

namespace In {

class Load : public Instruction {
public:
  typedef Simone::Ptr<const Load> PtrConst;
  typedef Simone::Ptr<Load> Ptr;

  static Ptr LoadNew(Simone::Ptr<Location> _src,
                     Simone::Ptr<Location> _dst);

  /* attribute member functions */
  Simone::Ptr<Location> src();
  Simone::Ptr<const Location> src() const;

  Simone::Ptr<Location> dst();
  Simone::Ptr<const Location> dst() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Load(Simone::Ptr<Location> _src, Simone::Ptr<Location> _dst);

  /* data members */
  Simone::Ptr<Location> src_;
  Simone::Ptr<Location> dst_;

  /* operations disallowed */
  Load(const Load&);
  void operator=(const Load&);
};

} /* end of namespace In */

#endif
