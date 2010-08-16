#include "label.h"

/* stl includes */
#include <sstream>
using std::ostringstream;

/* ast includes */
#include <ast/identifier.h>

namespace In {

Label::PtrConst Label::kPrintInt    = Label::LabelNew("_PrintInt");
Label::PtrConst Label::kPrintBool   = Label::LabelNew("_PrintBool");
Label::PtrConst Label::kPrintString = Label::LabelNew("_PrintString");

Label::Ptr
Label::LabelNew(Identifier::PtrConst _id) {
  return new Label(_id->name());
}

string
Label::str() const {
  ostringstream s;
  s << label_;

  return s.str();
}

const char *
Label::c_str() const {
  return this->str().c_str();
}


} /* end of namespace In */
