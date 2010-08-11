#ifndef MIPS_EMIT_FUNCTOR_H_HKD1N6TH
#define MIPS_EMIT_FUNCTOR_H_HKD1N6TH

#include "instruction/instruction.h"
#include "instruction_fwd_declarations.h"

class MIPSEmitFunctor : public Instruction::Functor {
public:
  typedef Simone::Ptr<const MIPSEmitFunctor> PtrConst;
  typedef Simone::Ptr<MIPSEmitFunctor> Ptr;

  static Ptr MIPSEmitFunctorNew() {
    return new MIPSEmitFunctor();
  }

  // void operator()(Instruction *) { ABORT(); }
  void operator()(LoadIntConst *);
  // void operator()(LoadStrConst *) {}
  // void operator()(LoadLabel *) {}
  // void operator()(Assign *) {}
  // void operator()(Load *) {}
  // void operator()(Store *) {}
  // void operator()(BinaryOp *) {}
  // void operator()(Label *) {}
  // void operator()(Goto *) {}
  // void operator()(IfZ *) {}
  // void operator()(BeginFunc *) {}
  // void operator()(EndFunc *) {}
  // void operator()(Return *) {}
  // void operator()(PushParam *) {}
  // void operator()(PopParams *) {}
  // void operator()(LCall *) {}
  // void operator()(ACall *) {}
  // void operator()(VTable *) {}

private:
  MIPSEmitFunctor() {}

  /* disallowed operations */
  MIPSEmitFunctor(const MIPSEmitFunctor&);
  void operator=(const MIPSEmitFunctor&);
};

#endif
