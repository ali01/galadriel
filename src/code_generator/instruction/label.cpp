#include "label.h"

/* ast includes */
#include <ast/identifier.h>

Label::Ptr
Label::LabelNew(Identifier::PtrConst _id) {
  return new Label(_id->name());
}