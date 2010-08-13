#ifndef A_CALL_H_6VISGMX4
#define A_CALL_H_6VISGMX4

/* local includes */
#include "fn_call.h"

/* forward declarations */
class Location;

namespace In {

class ACall : public FnCall {
public:
  typedef Simone::Ptr<const ACall> PtrConst;
  typedef Simone::Ptr<ACall> Ptr;

  static Ptr ACallNew(Simone::Ptr<Location> _fn_loc,
                      Simone::Ptr<Location> _ret_loc);

  /* attribute member functions */
  Simone::Ptr<Location> functionLocation();
  Simone::Ptr<const Location> functionLocation() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  ACall(Simone::Ptr<Location> _fn_loc, Simone::Ptr<Location> _ret_loc);

  /* data members */
  Simone::Ptr<Location> fn_loc_;

  /* operations disallowed */
  ACall(const ACall&);
  void operator=(const ACall&);
};


} /* end of namespace In */

#endif
