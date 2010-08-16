#ifndef STORE_H_YSIVAGVJ
#define STORE_H_YSIVAGVJ

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;

namespace In {

class Store : public Instruction {
public:
  typedef Simone::Ptr<const Store> PtrConst;
  typedef Simone::Ptr<Store> Ptr;

  static Ptr StoreNew(Simone::Ptr<const Location> _src,
                      Simone::Ptr<const Location> _dst);

  /* attribute member functions */
  Simone::Ptr<const Location> src();
  Simone::Ptr<const Location> src() const;

  Simone::Ptr<const Location> dst();
  Simone::Ptr<const Location> dst() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Store(Simone::Ptr<const Location> _src, Simone::Ptr<const Location> _dst);

  /* data members */
  Simone::Ptr<const Location> src_;
  Simone::Ptr<const Location> dst_;

  /* operations disallowed */
  Store(const Store&);
  void operator=(const Store&);
};

} /* end of namespace In */

#endif
