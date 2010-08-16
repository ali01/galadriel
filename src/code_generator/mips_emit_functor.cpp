#include "mips_emit_functor.h"

/* stl includes */
#include <iostream>
using std::cout;

/* local includes */
#include "instruction_includes.h"
#include "location_includes.h"
#include "tac_emit_functor.h"

const string MIPSEmitFunctor::kIndent = "  ";
const string MIPSEmitFunctor::kDelimit = "\n";


MIPSEmitFunctor::MIPSEmitFunctor() : reg_last_used_(zero), str_num_(0) {
  registers_[zero] = (Register){ false, NULL, "$zero", false };
  registers_[at]   = (Register){ false, NULL, "$at",   false };
  registers_[v0]   = (Register){ false, NULL, "$v0",   false };
  registers_[v1]   = (Register){ false, NULL, "$v1",   false };
  registers_[a0]   = (Register){ false, NULL, "$a0",   false };
  registers_[a1]   = (Register){ false, NULL, "$a1",   false };
  registers_[a2]   = (Register){ false, NULL, "$a2",   false };
  registers_[a3]   = (Register){ false, NULL, "$a3",   false };
  registers_[k0]   = (Register){ false, NULL, "$k0",   false };
  registers_[k1]   = (Register){ false, NULL, "$k1",   false };
  registers_[gp]   = (Register){ false, NULL, "$gp",   false };
  registers_[sp]   = (Register){ false, NULL, "$sp",   false };
  registers_[fp]   = (Register){ false, NULL, "$fp",   false };
  registers_[ra]   = (Register){ false, NULL, "$ra",   false };
  registers_[t0]   = (Register){ false, NULL, "$t0",   true };
  registers_[t1]   = (Register){ false, NULL, "$t1",   true };
  registers_[t2]   = (Register){ false, NULL, "$t2",   true };
  registers_[t3]   = (Register){ false, NULL, "$t3",   true };
  registers_[t4]   = (Register){ false, NULL, "$t4",   true };
  registers_[t5]   = (Register){ false, NULL, "$t5",   true };
  registers_[t6]   = (Register){ false, NULL, "$t6",   true };
  registers_[t7]   = (Register){ false, NULL, "$t7",   true };
  registers_[t8]   = (Register){ false, NULL, "$t8",   true };
  registers_[t9]   = (Register){ false, NULL, "$t9",   true };
  registers_[s0]   = (Register){ false, NULL, "$s0",   true };
  registers_[s1]   = (Register){ false, NULL, "$s1",   true };
  registers_[s2]   = (Register){ false, NULL, "$s2",   true };
  registers_[s3]   = (Register){ false, NULL, "$s3",   true };
  registers_[s4]   = (Register){ false, NULL, "$s4",   true };
  registers_[s5]   = (Register){ false, NULL, "$s5",   true };
  registers_[s6]   = (Register){ false, NULL, "$s6",   true };
  registers_[s7]   = (Register){ false, NULL, "$s7",   true };

  tac_emit_functor_ = TACEmitFunctor::TACEmitFunctorNew();
  tac_emit_functor_->indentOnIs(false);

  /* emitting preamble */
  emit("# standard Decaf preamble ", true);
  emit(".text");
  emit(".align 2");
  emit(".globl main");
}

void
MIPSEmitFunctor::operator()(In::LoadIntConst *in) {
  emit_tac_comment(in);

  int val = in->value();
  Location::PtrConst dst = in->dst();
  RegisterName reg = alloc_register(dst, kWrite);

  snprintf(buf_, sizeof buf_, "li %s, %d\t\t# load constant value %d into %s",
           registers_[reg].name_, val, val, registers_[reg].name_);

  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::LoadStrConst *in) {
  emit_tac_comment(in);

  str_num_++;
  string val = in->value();
  string label_str = "_string" + str_num_;

  snprintf(buf_, sizeof buf_, "%s: .asciiz %s", label_str.c_str(), val.c_str());
  emit(".data    # create string constant marked with label");
  emit(buf_);
  emit(".text");

  Location::PtrConst dst = in->dst();
  In::Label::Ptr label = In::Label::LabelNew(label_str);
  In::LoadLabel::Ptr load_label_i = In::LoadLabel::LoadLabelNew(dst, label);

  Functor::Ptr this_functor = this;
  this_functor(load_label_i);
}

void
MIPSEmitFunctor::operator()(In::LoadLabel *in) {
  emit_tac_comment(in);

  In::Label::PtrConst label = in->label();
  Location::PtrConst dst = in->dst();
  RegisterName reg = alloc_register(dst, kWrite);

  snprintf(buf_, sizeof buf_, "la %s, %s    # load label",
           registers_[reg].name_, label->c_str());
  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::Assign *in) {
  emit_tac_comment(in);

  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();
  RegisterName r_src = alloc_register(src, kRead);
  RegisterName r_dst = alloc_register(dst, kWrite);

  snprintf(buf_, sizeof buf_, "move %s, %s    # copy value",
           registers_[r_dst].name_, registers_[r_src].name_);
  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::Load *in) {
  emit_tac_comment(in);

  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();
  RegisterName r_src = alloc_register(src, kRead);
  RegisterName r_dst = alloc_register(dst, kWrite, r_src);

  int src_offset = src->secondaryOffset();

  snprintf(buf_, sizeof buf_, "lw %s, %d(%s)    # load with offset",
           registers_[r_dst].name_, src_offset, registers_[r_src].name_);
  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::Store *in) {
  emit_tac_comment(in);

  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();
  RegisterName r_src = alloc_register(src, kRead);
  RegisterName r_dst = alloc_register(dst, kRead, r_src);

  int dst_offset = dst->secondaryOffset();

  snprintf(buf_, sizeof buf_, "sw %s, %d(%s)    # store with offset",
           registers_[r_src].name_, dst_offset, registers_[r_dst].name_);
  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::BinaryOp *in) {
  emit_tac_comment(in);

  Location::PtrConst lhs = in->lhs();
  Location::PtrConst rhs = in->rhs();
  Location::PtrConst dst = in->dst();

  RegisterName r_lhs = alloc_register(lhs, kRead);
  RegisterName r_rhs = alloc_register(rhs, kRead, r_lhs);
  RegisterName r_dst = alloc_register(dst, kWrite, r_lhs, r_rhs);

  string code_str = op_str(in);

  snprintf(buf_, sizeof buf_, "%s %s, %s, %s", code_str.c_str(),
           registers_[r_dst].name_, registers_[r_lhs].name_, 
           registers_[r_rhs].name_);

  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::Label *in) {
  spill_dirty_registers();
  snprintf(buf_, sizeof buf_, "%s:", in->c_str());
  emit(buf_, true);
}

void
MIPSEmitFunctor::operator()(In::Goto *in) {
  spill_dirty_registers();
  In::Label::PtrConst label = in->label();
  snprintf(buf_, sizeof buf_, "b %s    # unconditional branch", label->c_str());
  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::IfZ *in) {
  emit_tac_comment(in);

  In::Label::PtrConst label = in->label();

  Location::PtrConst test_loc = in->test();
  RegisterName test_reg = alloc_register(test_loc, kRead);

  spill_dirty_registers();
  snprintf(buf_, sizeof buf_, "beqz %s, %s    # branch if %s is zero ", 
           registers_[test_reg].name_, label->c_str(), 
           test_loc->name().c_str());
  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::BeginFunc *in) {
  /* emitting label */
  In::Label::Ptr label = in->label();
  Functor::Ptr this_functor = this;
  this_functor(label);
  
  emit("# BeginFunc", true); // TODO: use tac functor (will require refactor)
  emit("subu $sp, $sp, 8    # decrement sp to make space to save ra, fp");
  emit("sw $fp, 8($sp)      # save fp");
  emit("sw $ra, 4($sp)      # save ra");
  emit("addiu $fp, $sp, 8   # set up new fp");

  In::BeginFunc::FrameSize frame_size = in->frameSize();
  if (frame_size > 0) {
    snprintf(buf_, sizeof buf_,
             "subu $sp, $sp, %lu   # decrement sp for locals/temps", 
             frame_size);
    emit(buf_);
  }
}

void
MIPSEmitFunctor::operator()(In::EndFunc *in) {
  emit_tac_comment(in);

  emit("# (below handles reaching end of fn_body with no explicit return)");

  Functor::Ptr this_functor = this;
  In::Return::Ptr ret_i = In::Return::ReturnNew(NULL);
  this_functor(ret_i);
}

void
MIPSEmitFunctor::operator()(In::Return *in) {
  emit_tac_comment(in);

  Location::PtrConst ret_loc = in->returnLocation();
  RegisterName r_ret_loc = alloc_register(ret_loc, kRead);
  if (ret_loc != NULL) {
    snprintf(buf_, sizeof buf_,
             "move $v0, %s    # copy return value into $v0",
             registers_[r_ret_loc].name_);
    emit(buf_);
  }

  spill_for_end_func();
  emit("move $sp, $fp      # pop callee frame off stack");
  emit("lw $ra, -4($fp)    # restore saved ra");
  emit("lw $fp, 0($fp)     # restore saved fp");
  emit("jr $ra             # return from function");
}

void
MIPSEmitFunctor::operator()(In::PushParam *in) {
  emit_tac_comment(in);

  Location::PtrConst param_loc = in->paramLocation();
  RegisterName reg = alloc_register(param_loc, kRead);

  emit("subu $sp, $sp, 4    # decrement sp to make space for param");
  snprintf(buf_, sizeof buf_, "sw %s, 4($sp)       # copy param value to stack", 
           registers_[reg].name_);
  emit(buf_);
}

void
MIPSEmitFunctor::operator()(In::PopParams *in) {
  emit_tac_comment(in);

  uint32_t bytes = in->bytes();
  if (bytes != 0) {
    snprintf(buf_, sizeof buf_, "add $sp, $sp, %u    # pop params off stack", 
             bytes);
    emit(buf_);
  }
}

void
MIPSEmitFunctor::operator()(In::FnCall *in) {
  Location::PtrConst ret_loc = in->returnLocation();

  if (ret_loc != NULL) {
    RegisterName reg = alloc_register(ret_loc, kWrite);
    snprintf(buf_, sizeof buf_,
             "move %s, %s    # copy function return value from $v0",  
             registers_[reg].name_, registers_[v0].name_);
    emit(buf_);
  }
}

void
MIPSEmitFunctor::operator()(In::LCall *in) {
  emit_tac_comment(in);

  spill_dirty_registers();

  In::Label::PtrConst label = in->label();
  snprintf(buf_, sizeof buf_, "jal %-15s    # jump to function label",
           label->c_str());
  emit(buf_);

  /* applying this functor on upcasted in */
  (*this)(static_cast<In::FnCall*>(in));
}

void
MIPSEmitFunctor::operator()(In::ACall *in) {
  emit_tac_comment(in);

  spill_dirty_registers();

  Location::PtrConst fn_loc = in->functionLocation();
  RegisterName reg = alloc_register(fn_loc, kRead);
  snprintf(buf_, sizeof buf_, "jalr %-15s    # jump to function address",
           registers_[reg].name_);
  emit(buf_);

  /* applying this functor on upcasted in */
  (*this)(static_cast<In::FnCall*>(in));
}

void
MIPSEmitFunctor::operator()(In::VTable *in) {
  emit_tac_comment(in);

  In::Label::PtrConst label = in->classLabel();
  snprintf(buf_, sizeof buf_, "%s:    # label for class %s vtable",
           label->c_str(), label->c_str());
  emit(".data");
  emit(".align 2");
  emit(buf_);

  In::Label::PtrConst fn_label;
  In::VTable::const_label_iter it = in->fnLabelsBegin();
  for (; it != in->fnLabelsEnd(); ++it) {
    fn_label = *it;
    snprintf(buf_, sizeof buf_, ".word %s\n", fn_label->c_str());
    emit(buf_);
  }

  emit(".text");
}

/* private interface */

void
MIPSEmitFunctor::emit(const string& _in_str, bool _supress_indent) const {
  if (not _supress_indent)
    cout << kIndent;

  cout << _in_str << kDelimit;
}

void
MIPSEmitFunctor::emit_tac_comment(In::Instruction::Ptr _in) const {
  cout << "# ";
  tac_emit_functor_(_in);
}

/* Member Function: register
 * -------------------
 * Given a location for a current var, a reason (kRead or kWrite)
 * and up to two registers to avoid, this method will assign
 * to a var to register trying these alternatives in order:
 *  1) if that var is already in a register ("same" is determined
 *     by matching name and same scope), we use that one
 *  2) find an empty register to use for the var
 *  3) find an in-use register that is not dirty.  We don't need
 *     to write value back to memory since it's clean, so we just
 *     replace with the new var
 *  4) spill an in-use, dirty register, by writing its contents to
 *     memory and then replace with the new var
 * For steps 3 & 4, we respect the registers given to avoid (ie the
 * other operands in this operation). The register descriptors are
 * updated to show the new state of the world. If for read, we
 * load the current value from memory into the register. If for
 * write, we mark the register as dirty (since it is getting a
 * new value).
 */
MIPSEmitFunctor::RegisterName
MIPSEmitFunctor::alloc_register(Location::PtrConst var,
                                RegPurpose reason,
                                RegisterName avoid1,
                                RegisterName avoid2) {
  RegisterName reg;

  if (!register_with_contents(var, reg)) {

    if (!register_with_contents(NULL, reg)) {
      reg = register_to_spill(avoid1, avoid2);
      spill_register(reg);
    }

    registers_[reg].var_ = var;

    if (reason == kRead) { /* load current value */
      assert(var->offset() % 4 == 0); /* all variables are 4 bytes */

      const char *segment;
      if (var->segment() == Location::kStack) {
        segment = registers_[fp].name_;
      } else {
        segment = registers_[gp].name_;
      }

      snprintf(buf_, sizeof buf_, "lw %s, %d(%s)\t# load %s from %s%+d into %s",
               registers_[reg].name_, var->offset(), segment,
               var->name().c_str(), segment, var->offset(),
               registers_[reg].name_);
      emit(buf_);

      registers_[reg].is_dirty_ = false;
    }
  }

  if (reason == kWrite)
    registers_[reg].is_dirty_ = true;

  return reg;
}


/* Member Function: register_to_spill
 * -----------------------------
 * Chooses an in-use register to replace with a new variable. We
 * prefer to replace a non-dirty once since we would not have to
 * write its contents back to memory, so the first loop searches
 * for a clean one. If none found, we take a dirty one.  In both
 * loops we deliberately won't choose either of the registers we
 * were asked to avoid.  We track the last dirty register spilled
 * and advance on each subsequent spill as a primitive means of
 * trying to not throw out things we just loaded and thus are likely
 * to need.
 */
MIPSEmitFunctor::RegisterName
MIPSEmitFunctor::register_to_spill(RegisterName avoid1, RegisterName avoid2) {
  /* first attempt to find a clean register */
  for (RegisterName i = zero; i < num_registers_; i = (RegisterName)(i+1)) {
    if (i != avoid1 && i != avoid2 &&
        registers_[i].is_general_purpose_ && !registers_[i].is_dirty_)
    {
      return i;
    }
  }

  do { /* otherwise just pick the next usable register */
    reg_last_used_ = (RegisterName)((reg_last_used_ + 1) % num_registers_);
  } while (reg_last_used_ == avoid1 || reg_last_used_ == avoid2 ||
           !registers_[reg_last_used_].is_general_purpose_);

  return reg_last_used_;
}


/* Member Function: spill_register
 * ---------------------
 * "Empties" register.  If variable is currently slaved in this register
 * and its contents are out of synch with memory (is_dirty_), we write back
 * the current contents to memory. We then clear the descriptor so we
 * realize the register is empty.
 */
void
MIPSEmitFunctor::spill_register(RegisterName reg)
{
  Location::PtrConst var = registers_[reg].var_;
  if (var && registers_[reg].is_dirty_) {

    const char *segment;
    if (var->segment() == Location::kStack) {
      segment = registers_[fp].name_;
    } else {
      segment = registers_[gp].name_;
    }

    assert(var->offset() % 4 == 0); /* all variables are 4 bytes in size */

    snprintf(buf_, sizeof buf_, "sw %s, %d(%s)\t# spill %s from %s to %s%+d",
             registers_[reg].name_, var->offset(), segment, var->name().c_str(),
             registers_[reg].name_, segment,var->offset());

    emit(buf_);
  }

  registers_[reg].var_ = NULL;
}


/* Member Function: spill_dirty_registers
 * ------------------------------
 * Used before flow of control change (branch, label, jump, etc.) to
 * save contents of all dirty registers. This synchs the contents of
 * the registers with the memory locations for the variables.
 */
void
MIPSEmitFunctor::spill_dirty_registers() {
  RegisterName i;

  for (i = zero; i < num_registers_; i = (RegisterName)(i+1)) {
    if (registers_[i].var_ && registers_[i].is_dirty_)
      break;
  }

  if (i != num_registers_){
    /* only print if at least one register is dirty */
    emit("# (save modified registers before flow of control change)");
  }

  for (i = zero; i < num_registers_; i = (RegisterName)(i+1)) {
    spill_register(i);
  }
}


/* Member Function: spill_for_end_func
 * ---------------------------
 * Slight optimization on the above method used when spilling for
 * end of function (return/fall off). In such a case, we do not
 * need to save values for locals, temps, and parameters because the
 * function is about to exit and those variables are going away
 * immediately, so no need to bother with updating contents.
 */
void
MIPSEmitFunctor::spill_for_end_func() {
  for (RegisterName i = zero; i < num_registers_; i = (RegisterName)(i+1)) {
    if (registers_[i].is_general_purpose_ && registers_[i].var_) {
      if (registers_[i].var_->segment() == Location::kData) {
        spill_register(i);
      } else {
        /* all stack variables can just be discarded */
        registers_[i].var_ = NULL;
      }
    }
  }
}

/* Member Function: register_with_contents
 * --------------------------------
 * Searches the descriptors for one with contents var. Assigns
 * register by reference, and returns true/false on whether match found.
 */
bool
MIPSEmitFunctor::register_with_contents(Location::PtrConst var, RegisterName& reg) {
  for (reg = zero; reg < num_registers_; reg = (RegisterName)(reg+1)) {
    Location::PtrConst rvar = registers_[reg].var_;
    bool locations_equal = (var == rvar || (var && rvar && *var == *rvar));
    if (registers_[reg].is_general_purpose_ && locations_equal)
      return true;
  }

  return false;
}

string
MIPSEmitFunctor::op_str(In::BinaryOp::PtrConst _op) {
  switch (_op->op_code()) {
    case In::BinaryOp::kAdd:      return "add";
    case In::BinaryOp::kSubtract: return "sub";
    case In::BinaryOp::kMultiply: return "mul";
    case In::BinaryOp::kDivide:   return "div";
    case In::BinaryOp::kModulo:   return "rem";
    case In::BinaryOp::kEqual:    return "seq";
    case In::BinaryOp::kLess:     return "slt";
    case In::BinaryOp::kAnd:      return "and";
    case In::BinaryOp::kOr:       return "or";
  }

  return "(unknown operator)";
}
