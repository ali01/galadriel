#ifndef L_CALL_H_LXUNJQOG
#define L_CALL_H_LXUNJQOG

/* local includes */
#include "fn_call.h"

/* forward declarations */
class Location;

namespace In {

/* forward declarations */
class Label;

class LCall : public FnCall {
public:
  typedef Simone::Ptr<const LCall> PtrConst;
  typedef Simone::Ptr<LCall> Ptr;

  static Ptr LCallNew(Simone::Ptr<const Label> _label,
                      Simone::Ptr<Location> _return_loc);

  /* attribute member functions */
  Simone::Ptr<const Label> label() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  LCall(Simone::Ptr<const Label> _label,
        Simone::Ptr<Location> _return_loc);

  /* data members */
  Simone::Ptr<const Label> label_;

  /* operations disallowed */
  LCall(const LCall&);
  void operator=(const LCall&);
};

} /* end of namespace In */

#endif
