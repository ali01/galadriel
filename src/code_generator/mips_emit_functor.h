#ifndef MIPS_EMIT_FUNCTOR_H_HKD1N6TH
#define MIPS_EMIT_FUNCTOR_H_HKD1N6TH

#include "instruction/instruction.h"
#include "instruction_fwd_declarations.h"

class MIPSEmitFunctor : public In::Instruction::Functor {
public:
  typedef Simone::Ptr<const MIPSEmitFunctor> PtrConst;
  typedef Simone::Ptr<MIPSEmitFunctor> Ptr;

  static Ptr MIPSEmitFunctorNew() {
    return new MIPSEmitFunctor();
  }

  // void operator()(In::Instruction *) { ABORT(); }
  void operator()(In::LoadIntConst *);
  // void operator()(In::LoadStrConst *);
  // void operator()(In::LoadLabel *);
  // void operator()(In::Assign *);
  // void operator()(In::Load *);
  // void operator()(In::Store *);
  // void operator()(In::BinaryOp *);
  // void operator()(In::Label *);
  // void operator()(In::Goto *);
  // void operator()(In::IfZ *);
  // void operator()(In::BeginFunc *);
  // void operator()(In::EndFunc *);
  // void operator()(In::Return *);
  // void operator()(In::PushParam *);
  // void operator()(In::PopParams *);
  // void operator()(In::LCall *);
  // void operator()(In::ACall *);
  // void operator()(In::VTable *);

private:
  MIPSEmitFunctor() {}

  /* disallowed operations */
  MIPSEmitFunctor(const MIPSEmitFunctor&);
  void operator=(const MIPSEmitFunctor&);
};

#endif
