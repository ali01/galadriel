#include "tac_emit_functor.h"

/* stl includes */
#include <string>
#include <iostream>
using std::string;
using std::cout;

#include "instruction_includes.h"
#include "location.h"

void
TACEmitFunctor::operator()(LoadIntConst *nd) {
  Location::PtrConst loc = nd->location();
  cout << loc->name() << " = " << nd->value();
}

void
TACEmitFunctor::operator()(LoadStrConst *nd) {
  Location::PtrConst loc = nd->location();
  cout << loc->name() << " = \"" << nd->value() << "\"";
}

void
TACEmitFunctor::operator()(Label *nd) {
  cout << *nd << ":\n";
}

void
TACEmitFunctor::operator()(BeginFunc *nd) {
  /* emitting label */
  Label::Ptr label = nd->label();
  Functor::Ptr this_functor = this;
  this_functor(label);

  /* emitting BeginFunc statement */
  BeginFunc::FrameSize f_size = nd->frameSize();
  if (f_size != BeginFunc::kInvalidFrameSize) {
    cout << "BeginFunc " << f_size;
  } else {
    cout << "BeginFunc (unassigned)";
  }
}

void
TACEmitFunctor::operator()(LCall *nd) {
  Location::PtrConst ret_loc = nd->returnLocation();
  if (ret_loc != NULL)
    cout << ret_loc->name() << " = ";

  cout << *nd->label();
}
