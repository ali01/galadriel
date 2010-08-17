#ifndef LOAD_LABEL_H_HOX13648
#define LOAD_LABEL_H_HOX13648

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;
class Label;

namespace In {

class LoadLabel : public Instruction {
public:
  typedef Simone::Ptr<const LoadLabel> PtrConst;
  typedef Simone::Ptr<LoadLabel> Ptr;

  static Ptr LoadLabelNew(Simone::Ptr<Location> _loc,
                          Simone::Ptr<Label> _label);

  /* attribute member functions */
  Simone::Ptr<Location> dst();
  Simone::Ptr<Location> dst() const;

  Simone::Ptr<Label> label();
  Simone::Ptr<const Label> label() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  LoadLabel(Simone::Ptr<Location> _loc, Simone::Ptr<Label> _label);

  /* data members */
  Simone::Ptr<Location> dst_;
  Simone::Ptr<Label> label_;

  /* operations disallowed */
  LoadLabel(const LoadLabel&);
  void operator=(const LoadLabel&);
};

} /* end of namespace In */

#endif
