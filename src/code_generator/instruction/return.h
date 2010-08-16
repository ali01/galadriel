#ifndef RETURN_H_7VVYJIVH
#define RETURN_H_7VVYJIVH

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;

namespace In {

class Return : public Instruction {
public:
  typedef Simone::Ptr<const Return> PtrConst;
  typedef Simone::Ptr<Return> Ptr;

  static Ptr ReturnNew(Simone::Ptr<const Location> _ret);

  /* attribute member functions */
  Simone::Ptr<const Location> returnLocation();
  Simone::Ptr<const Location> returnLocation() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Return(Simone::Ptr<const Location> _ret);

  /* data members */
  Simone::Ptr<const Location> ret_loc_;

  /* operations disallowed */
  Return(const Return&);
  void operator=(const Return&);
};


} /* end of namespace In */

#endif
