#include "tac_emit_functor.h"

/* stl includes */
#include <string>
#include <iostream>
using std::string;
using std::cout;

#include "location.h"
#include "instruction_includes.h"

void
TACEmitFunctor::operator()(In::LoadIntConst *in) {
  Location::PtrConst loc = in->location();
  cout << loc->name() << " = " << in->value();
}

void
TACEmitFunctor::operator()(In::LoadStrConst *in) {
  Location::PtrConst loc = in->location();
  cout << loc->name() << " = \"" << in->value() << "\"";
}

void
TACEmitFunctor::operator()(In::LoadLabel *in) {
  Location::PtrConst loc = in->location();
  cout << loc->name() << " = " << *in->label();
}

void
TACEmitFunctor::operator()(In::Load *in) {
  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();

  cout << dst->name() << " = " << "*(";

  if (src->secondaryOffset() != 0) {
    cout << src->name() << " + " << src->secondaryOffset() << ")";
  } else {
    cout << src->name() << ")";
  }
}

void
TACEmitFunctor::operator()(In::Assign *in) {
  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();
  cout << dst->name() << " = " << src->name();
}

void
TACEmitFunctor::operator()(In::Store *in) {
  Location::PtrConst src = in->src();
  Location::PtrConst dst = in->dst();

  if (src->secondaryOffset() != 0) {
    cout << "*(" << dst->name() << " + " << src->secondaryOffset() << ")";
  } else {
    cout << "*(" << dst->name() << ")";
  }

  cout << " = " << src->name();
}

void
TACEmitFunctor::operator()(In::BinaryOp *in) {
  Location::PtrConst dst = in->dst();
  Location::PtrConst lhs = in->lhs();
  Location::PtrConst rhs = in->rhs();

  cout << dst->name() << " = ";
  cout << lhs->name() << " " << in->op_str() << " " << rhs->name();
}

void
TACEmitFunctor::operator()(In::Label *in) {
  cout << *in << ":\n";
}

void
TACEmitFunctor::operator()(In::Goto *in) {
  cout << "Goto " << *in->label();
}

void
TACEmitFunctor::operator()(In::IfZ *in) {
  Location::PtrConst test = in->test();
  cout << "IfZ " << test->name() << " Goto " << *in->label();
}

void
TACEmitFunctor::operator()(In::BeginFunc *in) {
  /* emitting label */
  In::Label::Ptr label = in->label();
  Functor::Ptr this_functor = this;
  this_functor(label);

  /* emitting BeginFunc statement */
  In::BeginFunc::FrameSize f_size = in->frameSize();
  if (f_size != In::BeginFunc::kInvalidFrameSize) {
    cout << "BeginFunc " << f_size;
  } else {
    cout << "BeginFunc (unassigned)";
  }
}

void
TACEmitFunctor::operator()(In::LCall *in) {
  Location::PtrConst ret_loc = in->returnLocation();
  if (ret_loc != NULL)
    cout << ret_loc->name() << " = ";

  cout << *in->label();
}
