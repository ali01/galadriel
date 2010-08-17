#ifndef ASSIGN_H_LG0TY6E7
#define ASSIGN_H_LG0TY6E7

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;

/* instruction namespace */
namespace In {

class Assign : public Instruction {
public:
  typedef Simone::Ptr<const Assign> PtrConst;
  typedef Simone::Ptr<Assign> Ptr;

  static Ptr AssignNew(Simone::Ptr<Location> _src,
                       Simone::Ptr<Location> _dst);

  /* attribute member functions */
  Simone::Ptr<Location> src();
  Simone::Ptr<Location> src() const;
  
  Simone::Ptr<Location> dst();
  Simone::Ptr<Location> dst() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Assign(Simone::Ptr<Location> src, Simone::Ptr<Location> dst);

  /* data members */
  Simone::Ptr<Location> src_;
  Simone::Ptr<Location> dst_;

  /* operations disallowed */
  Assign(const Assign&);
  void operator=(const Assign&);
};

} /* end of namespace In */

#endif
