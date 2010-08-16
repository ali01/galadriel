#ifndef IFZ_H_LGXOGCN9
#define IFZ_H_LGXOGCN9

/* local includes */
#include "instruction.h"

/* forward declarations */
class Label;
class Location;

namespace In {

class IfZ : public Instruction {
public:
  typedef Simone::Ptr<const IfZ> PtrConst;
  typedef Simone::Ptr<IfZ> Ptr;

  static Ptr IfZNew(Simone::Ptr<const Location> _test, Simone::Ptr<Label> _label);

  /* attribute member functions */
  Simone::Ptr<const Location> test();
  Simone::Ptr<const Location> test() const;

  Simone::Ptr<Label> label();
  Simone::Ptr<const Label> label() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  IfZ(Simone::Ptr<const Location> _test, Simone::Ptr<Label> _label);

  /* data members */
  Simone::Ptr<const Location> test_;
  Simone::Ptr<Label> label_;

  /* operations disallowed */
  IfZ(const IfZ&);
  void operator=(const IfZ&);
};


} /* end of namespace In */

#endif
