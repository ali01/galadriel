#ifndef GOTO_H_49UML1C
#define GOTO_H_49UML1C

/* local includes */
#include "instruction.h"

/* forward declarations */
class Label;

namespace In {

class Goto : public Instruction {
public:
  typedef Simone::Ptr<const Goto> PtrConst;
  typedef Simone::Ptr<Goto> Ptr;

  static Ptr GotoNew(Simone::Ptr<Label> _label);

  /* attribute member functions */
  Simone::Ptr<Label> label();
  Simone::Ptr<const Label> label() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Goto(Simone::Ptr<Label> label);

  /* data members */
  Simone::Ptr<Label> label_;

  /* operations disallowed */
  Goto(const Goto&);
  void operator=(const Goto&);
};


} /* end of namespace In */

#endif
