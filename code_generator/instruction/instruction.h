#ifndef INSTRUCTION_H_RI9MUBTK
#define INSTRUCTION_H_RI9MUBTK

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/utility.h>

/* local includes */
#include "../instruction_fwd_declarations.h"

namespace In {

class Instruction : public Simone::PtrInterface<Instruction> {
public:
  typedef Simone::Ptr<const Instruction> PtrConst;
  typedef Simone::Ptr<Instruction> Ptr;

  /* support for double dispatch */
  class Functor : public Simone::PtrInterface<Functor> {
    public:
      typedef Simone::Ptr<Functor> Ptr;
      typedef Simone::Ptr<const Functor> PtrConst;

      /* top level */
      virtual void operator()(LoadIntConst *) {}
      virtual void operator()(LoadStrConst *) {}
      virtual void operator()(LoadLabel *) {}
      virtual void operator()(Assign *) {}
      virtual void operator()(Load *) {}
      virtual void operator()(Store *) {}
      virtual void operator()(BinaryOp *) {}
      virtual void operator()(Label *) {}
      virtual void operator()(Goto *) {}
      virtual void operator()(IfZ *) {}
      virtual void operator()(BeginFunc *) {}
      virtual void operator()(EndFunc *) {}
      virtual void operator()(Return *) {}
      virtual void operator()(PushParam *) {}
      virtual void operator()(PopParams *) {}
      virtual void operator()(VTable *) {}

      /* fn_call */
      virtual void operator()(FnCall *) { ABORT(); }
      virtual void operator()(LCall *) {}
      virtual void operator()(ACall *) {}
  };

  /* support for double dispatch */
  virtual void self_apply(Functor::Ptr _functor) = 0;

protected:
  Instruction() {}
  virtual ~Instruction() {}

private:
  /* data members */

  /* disallowed operations */
  Instruction(const Instruction&);
  void operator=(const Instruction&);
};

} /* end of namespace In */

#endif
