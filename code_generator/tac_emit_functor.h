#ifndef TAC_EMITTER_H_HKKQ4WIR
#define TAC_EMITTER_H_HKKQ4WIR

/* stl includes */
#include <string>
using std::string;

/* instruction includes */
#include "instruction_fwd_declarations.h"
#include "instruction/instruction.h"


class TACEmitFunctor : public In::Instruction::Functor {
public:
  typedef Simone::Ptr<const TACEmitFunctor> PtrConst;
  typedef Simone::Ptr<TACEmitFunctor> Ptr;

  static const string kIndent;
  static const string kDelimit;

  static Ptr TACEmitFunctorNew() {
    return new TACEmitFunctor();
  }

  bool indentOn() const { return indent_on_; }
  void indentOnIs(bool _s) { indent_on_ = _s; }

  /* functor operators */
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
  void operator()(In::EndFunc *);
  void operator()(In::Return *);
  void operator()(In::PushParam *);
  void operator()(In::PopParams *);
  void operator()(In::VTable *);

  /* void operator()(In::FnCall *); */
  void operator()(In::LCall *);
  void operator()(In::ACall *);

private:
  TACEmitFunctor() : indent_on_(true) {}

  /* private member functions */
  void emit(const string& _in_str,
            bool _supress_indent=false,
            bool _supress_delimit=false) const;

  /* data members */
  bool indent_on_;

  /* disallowed operations */
  TACEmitFunctor(const TACEmitFunctor&);
  void operator=(const TACEmitFunctor&);
};

#endif
