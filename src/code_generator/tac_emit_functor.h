#ifndef TAC_EMITTER_H_HKKQ4WIR
#define TAC_EMITTER_H_HKKQ4WIR

#include "instruction/instruction.h"
#include "instruction_fwd_declarations.h"

class TACEmitFunctor : public In::Instruction::Functor {
public:
  typedef Simone::Ptr<const TACEmitFunctor> PtrConst;
  typedef Simone::Ptr<TACEmitFunctor> Ptr;

  static Ptr TACEmitFunctorNew() {
    return new TACEmitFunctor();
  }

  void operator()(In::LoadIntConst *);
  void operator()(In::LoadStrConst *);
  void operator()(In::LoadLabel *);
  void operator()(In::Load *);
  void operator()(In::Assign *);
  void operator()(In::Store *);
  void operator()(In::BinaryOp *);
  void operator()(In::Label *);
  void operator()(In::Goto *);
  void operator()(In::IfZ *);
  void operator()(In::BeginFunc *);
  // void operator()(In::EndFunc *);
  // void operator()(In::Return *);
  // void operator()(In::PushParam *);
  // void operator()(In::PopParams *);
  void operator()(In::LCall *);
  // void operator()(In::ACall *);
  // void operator()(In::VTable *);

private:
  TACEmitFunctor() {}

  /* disallowed operations */
  TACEmitFunctor(const TACEmitFunctor&);
  void operator=(const TACEmitFunctor&);
};

#endif
