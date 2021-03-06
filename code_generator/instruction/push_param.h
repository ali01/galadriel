#ifndef PUSH_PARAM_H_QXZ12TMH
#define PUSH_PARAM_H_QXZ12TMH

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;

namespace In {

class PushParam : public Instruction {
public:
  typedef Simone::Ptr<const PushParam> PtrConst;
  typedef Simone::Ptr<PushParam> Ptr;

  static Ptr PushParamNew(Simone::Ptr<Location> _param_loc);

  /* attribute member functions */
  Simone::Ptr<Location> paramLocation();
  Simone::Ptr<Location> paramLocation() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  PushParam(Simone::Ptr<Location> _param_loc);

  /* data members */
  Simone::Ptr<Location> param_loc_;

  /* operations disallowed */
  PushParam(const PushParam&);
  void operator=(const PushParam&);
};

} /* end of namespace In */

#endif
