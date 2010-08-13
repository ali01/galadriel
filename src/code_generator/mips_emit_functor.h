#ifndef MIPS_EMIT_FUNCTOR_H_HKD1N6TH
#define MIPS_EMIT_FUNCTOR_H_HKD1N6TH

/* stl includes */
#include <string>
using std::string;

/* code_generator/instruction includes */
#include "instruction/instruction.h"
#include "instruction/binary_op.h"

/* local includes */
#include "instruction_fwd_declarations.h"

/* forward declarations */
class Location;
class TACEmitFunctor;


class MIPSEmitFunctor : public In::Instruction::Functor {
  /* private definitions */
  enum RegisterName {
    zero, at, v0, v1, a0, a1, a2, a3,
    t0, t1, t2, t3, t4, t5, t6, t7,
    s0, s1, s2, s3, s4, s5, s6, s7,
    t8, t9, k0, k1, gp, sp, fp, ra,
    num_registers_
  };

  enum RegPurpose { kRead, kWrite };

  struct Register {
    bool is_dirty_;
    Simone::Ptr<Location> var_;
    const char *name_;
    bool is_general_purpose_;
  } registers_[num_registers_];

public:
  typedef Simone::Ptr<const MIPSEmitFunctor> PtrConst;
  typedef Simone::Ptr<MIPSEmitFunctor> Ptr;

  static const string kIndent;
  static const string kDelimit;

  static Ptr MIPSEmitFunctorNew() {
    return new MIPSEmitFunctor();
  }

  /* top level */
  void operator()(In::LoadIntConst *);
  void operator()(In::LoadStrConst *);
  void operator()(In::LoadLabel *);
  void operator()(In::Assign *);
  void operator()(In::Load *);
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

  /* fn_decl */
  void operator()(In::FnCall *);
  void operator()(In::LCall *);
  void operator()(In::ACall *);

private:
  MIPSEmitFunctor();

  /* -- member functions -- */

  void emit(const string& _in_str, bool _supress_indent=false) const;
  void emit_tac_comment(In::Instruction::Ptr _in) const;

  RegisterName alloc_register(Simone::Ptr<Location> var,
                              RegPurpose reason,
                              RegisterName avoid1=zero,
                              RegisterName avoid2=zero);

  RegisterName register_to_spill(RegisterName avoid1, RegisterName avoid2);
  void spill_register(RegisterName reg);
  void spill_dirty_registers();
  void spill_for_end_func();

  bool register_with_contents(Simone::Ptr<Location> var, RegisterName& reg);

  static string op_str(In::BinaryOp::PtrConst _op);


  /* -- data members -- */
  
  RegisterName reg_last_used_;
  Simone::Ptr<TACEmitFunctor> tac_emit_functor_;
  char buf_[512];

  /* used to keep track of the number of string constants allocated */
  uint32_t str_num_;

  /* disallowed operations */
  MIPSEmitFunctor(const MIPSEmitFunctor&);
  void operator=(const MIPSEmitFunctor&);
};

#endif
