#include "tac_emit_functor.h"

/* stl includes */
#include <string>
#include <sstream>
#include <iostream>
using std::cout;
using std::ostringstream;
using std::string;


#include "location/location.h"
#include "instruction_includes.h"

const string TACEmitFunctor::kIndent = "  ";
const string TACEmitFunctor::kDelimit = ";\n";

void
TACEmitFunctor::operator()(In::LoadIntConst *in) {
  ostringstream s;

  Location::PtrConst loc = in->dst();
  s << loc->name() << " = " << in->value();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::LoadStrConst *in) {
  ostringstream s;

  Location::PtrConst loc = in->dst();
  s << loc->name() << " = \"" << in->value() << "\"";

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::LoadLabel *in) {
  ostringstream s;

  Location::PtrConst loc = in->dst();
  s << loc->name() << " = " << *in->label();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::Load *in) {
  ostringstream s;

  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();

  s << dst->name() << " = " << "*(";

  if (src->secondaryOffset() != 0) {
    s << src->name() << " + " << src->secondaryOffset() << ")";
  } else {
    s << src->name() << ")";
  }

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::Assign *in) {
  ostringstream s;

  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();
  s << dst->name() << " = " << src->name();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::Store *in) {
  ostringstream s;

  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();

  if (src->secondaryOffset() != 0) {
    s << "*(" << dst->name() << " + " << src->secondaryOffset() << ")";
  } else {
    s << "*(" << dst->name() << ")";
  }

  s << " = " << src->name();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::BinaryOp *in) {
  ostringstream s;

  Location::PtrConst dst = in->dst();
  Location::PtrConst lhs = in->lhs();
  Location::PtrConst rhs = in->rhs();

  s << dst->name() << " = ";
  s << lhs->name() << " " << in->op_str() << " " << rhs->name();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::Label *in) {
  ostringstream s;
  s << *in << ":\n";

  emit(s.str(), true);
}

void
TACEmitFunctor::operator()(In::Goto *in) {
  ostringstream s;
  s << "Goto " << *in->label();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::IfZ *in) {
  ostringstream s;
  Location::PtrConst test = in->test();

  s << "IfZ " << test->name() << " Goto " << *in->label();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::BeginFunc *in) {
  ostringstream s;

  /* emitting label */
  In::Label::Ptr label = in->label();
  Functor::Ptr this_functor = this;
  this_functor(label);

  /* emitting BeginFunc statement */
  In::BeginFunc::FrameSize f_size = in->frameSize();
  if (f_size != In::BeginFunc::kInvalidFrameSize) {
    s << "BeginFunc " << f_size;
  } else {
    s << "BeginFunc (unassigned)";
  }

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::EndFunc *in) {
  ostringstream s;
  s << "EndFunc";

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::Return *in) {
  ostringstream s;
  Location::PtrConst ret_loc = in->returnLocation();
  s << "Return";

  if (ret_loc)
    s << " " << ret_loc->name();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::PushParam *in) {
  ostringstream s;
  Location::PtrConst param_loc = in->paramLocation();
  s << "PushParam " << param_loc->name();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::PopParams *in) {
  ostringstream s;
  s << "PopParams " << in->bytes();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::LCall *in) {
  ostringstream s;

  Location::PtrConst ret_loc = in->returnLocation();
  if (ret_loc != NULL)
    s << ret_loc->name() << " = ";

  s << *in->label();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::ACall *in) {
  ostringstream s;

  Location::PtrConst ret_loc = in->returnLocation();
  Location::PtrConst fn_loc = in->functionLocation();

  if (ret_loc != NULL)
    s << ret_loc->name() << " = ";

  s << fn_loc->name();

  emit(s.str());
}

void
TACEmitFunctor::operator()(In::VTable *in) {
  ostringstream s;

  In::Label::PtrConst class_label = in->classLabel();
  s << "VTable " << *class_label << " =\n";

  In::Label::PtrConst fn_label;
  In::VTable::const_label_iter it = in->fnLabelsBegin();
  for (; it != in->fnLabelsEnd(); ++it) {
    fn_label = *it;
    s << "  " << *fn_label << ",\n";
  }

  emit(s.str());
}


/* private interface */

void
TACEmitFunctor::emit(const string& _in_str, bool _supress_indent) const {
  if (indent_on_ == true && _supress_indent == false)
    cout << kIndent;

  cout << _in_str << kDelimit;
}
