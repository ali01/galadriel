#include "tac_emit_functor.h"

/* stl includes */
#include <string>
#include <iostream>
using std::string;
using std::cout;

#include "location.h"
#include "instruction_includes.h"

const string TACEmitFunctor::kIndent = "  ";
const string TACEmitFunctor::kDelimit = ";\n";

void
TACEmitFunctor::operator()(In::LoadIntConst *in) {
  Location::PtrConst loc = in->location();
  cout << kIndent<< loc->name() << " = " << in->value() << kDelimit;
}

void
TACEmitFunctor::operator()(In::LoadStrConst *in) {
  Location::PtrConst loc = in->location();
  cout << kIndent << loc->name() << " = \"" << in->value() << "\"" << kDelimit;
}

void
TACEmitFunctor::operator()(In::LoadLabel *in) {
  Location::PtrConst loc = in->location();
  cout << kIndent << loc->name() << " = " << *in->label() << kDelimit;
}

void
TACEmitFunctor::operator()(In::Load *in) {
  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();

  cout << kIndent;
  cout << dst->name() << " = " << "*(";

  if (src->secondaryOffset() != 0) {
    cout << src->name() << " + " << src->secondaryOffset() << ")";
  } else {
    cout << src->name() << ")";
  }

  cout << kDelimit;
}

void
TACEmitFunctor::operator()(In::Assign *in) {
  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();
  cout << kIndent << dst->name() << " = " << src->name() << kDelimit;
}

void
TACEmitFunctor::operator()(In::Store *in) {
  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();

  cout << kIndent;

  if (src->secondaryOffset() != 0) {
    cout << "*(" << dst->name() << " + " << src->secondaryOffset() << ")";
  } else {
    cout << "*(" << dst->name() << ")";
  }

  cout << " = " << src->name() << kDelimit;
}

void
TACEmitFunctor::operator()(In::BinaryOp *in) {
  Location::PtrConst dst = in->dst();
  Location::PtrConst lhs = in->lhs();
  Location::PtrConst rhs = in->rhs();

  cout << kIndent;
  cout << dst->name() << " = ";
  cout << lhs->name() << " " << in->op_str() << " " << rhs->name();
  cout << kDelimit;
}

void
TACEmitFunctor::operator()(In::Label *in) {
  cout << *in << ":\n";
}

void
TACEmitFunctor::operator()(In::Goto *in) {
  cout << kIndent << "Goto " << *in->label() << kDelimit;
}

void
TACEmitFunctor::operator()(In::IfZ *in) {
  Location::PtrConst test = in->test();

  cout << kIndent;
  cout << "IfZ " << test->name() << " Goto " << *in->label() << kDelimit;
}

void
TACEmitFunctor::operator()(In::BeginFunc *in) {
  /* emitting label */
  In::Label::Ptr label = in->label();
  Functor::Ptr this_functor = this;
  this_functor(label);

  cout << kIndent;

  /* emitting BeginFunc statement */
  In::BeginFunc::FrameSize f_size = in->frameSize();
  if (f_size != In::BeginFunc::kInvalidFrameSize) {
    cout << "BeginFunc " << f_size;
  } else {
    cout << "BeginFunc (unassigned)";
  }

  cout << kDelimit;
}

void
TACEmitFunctor::operator()(In::EndFunc *in) {
  cout << kIndent << "EndFunc" << kDelimit;
}

void
TACEmitFunctor::operator()(In::Return *in) {
  Location::PtrConst ret_loc = in->returnLocation();
  cout << kIndent << "Return";

  if (ret_loc)
    cout << " " << ret_loc->name();

  cout << kDelimit;
}

void
TACEmitFunctor::operator()(In::PushParam *in) {
  Location::PtrConst param_loc = in->paramLocation();
  cout << kIndent << "PushParam " << param_loc->name() << kDelimit;
}

void
TACEmitFunctor::operator()(In::PopParams *in) {
  cout << kIndent << "PopParams " << in->bytes() << kDelimit;
}

void
TACEmitFunctor::operator()(In::LCall *in) {
  Location::PtrConst ret_loc = in->returnLocation();

  cout << kIndent;

  if (ret_loc != NULL)
    cout << ret_loc->name() << " = ";

  cout << *in->label() << kDelimit;
}

void
TACEmitFunctor::operator()(In::ACall *in) {
  Location::PtrConst ret_loc = in->returnLocation();
  Location::PtrConst fn_loc = in->functionLocation();

  cout << kIndent;

  if (ret_loc != NULL)
    cout << ret_loc->name() << " = ";

  cout << fn_loc->name() << kDelimit;
}

void
TACEmitFunctor::operator()(In::VTable *in) {
  In::Label::PtrConst class_label = in->classLabel();
  cout << kIndent << "VTable " << *class_label << " =\n";

  In::Label::PtrConst fn_label;
  In::VTable::const_label_iter it = in->fnLabelsBegin();
  for (; it != in->fnLabelsEnd(); ++it) {
    fn_label = *it;
    cout << "  " << *fn_label << ",\n";
  }

  cout << kDelimit;
}
