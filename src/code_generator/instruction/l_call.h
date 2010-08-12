#ifndef L_CALL_H_LXUNJQOG
#define L_CALL_H_LXUNJQOG

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;


namespace In {

/* forward declarations */
class Label;

class LCall : public Instruction {
public:
  typedef Simone::Ptr<const LCall> PtrConst;
  typedef Simone::Ptr<LCall> Ptr;

  static Ptr LCallNew(Simone::Ptr<Label> _label,
                      Simone::Ptr<Location> _return_loc);

  /* attribute member functions */
  Simone::Ptr<Label> label();
  Simone::Ptr<const Label> label() const;

  Simone::Ptr<Location> returnLocation();
  Simone::Ptr<const Location> returnLocation() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  LCall(Simone::Ptr<Label> _label,
        Simone::Ptr<Location> _return_loc);

  /* data members */
  Simone::Ptr<Label> label_;
  Simone::Ptr<Location> return_loc_;

  /* operations disallowed */
  LCall(const LCall&);
  void operator=(const LCall&);
};

} /* end of namespace In */

#endif
