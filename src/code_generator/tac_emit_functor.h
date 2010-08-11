#ifndef TAC_EMITTER_H_HKKQ4WIR
#define TAC_EMITTER_H_HKKQ4WIR

#include "instruction/instruction.h"
#include "instruction_fwd_declarations.h"

class TACEmitFunctor : public Instruction::Functor {
public:
  typedef Simone::Ptr<const TACEmitFunctor> PtrConst;
  typedef Simone::Ptr<TACEmitFunctor> Ptr;

  static Ptr TACEmitFunctorNew() {
    return new TACEmitFunctor();
  }

  void operator()(LoadIntConst *);
  void operator()(LoadStrConst *);
  // void operator()(LoadLabel *);
  // void operator()(Assign *);
  // void operator()(Load *);
  // void operator()(Store *);
  // void operator()(BinaryOp *);
  void operator()(Label *);
  // void operator()(Goto *);
  // void operator()(IfZ *);
  void operator()(BeginFunc *);
  // void operator()(EndFunc *);
  // void operator()(Return *);
  // void operator()(PushParam *);
  // void operator()(PopParams *);
  void operator()(LCall *);
  // void operator()(ACall *);
  // void operator()(VTable *);

private:
  TACEmitFunctor() {}

  /* disallowed operations */
  TACEmitFunctor(const TACEmitFunctor&);
  void operator=(const TACEmitFunctor&);
};

#endif
