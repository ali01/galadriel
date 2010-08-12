#include "label.h"

/* ast includes */
#include <ast/identifier.h>

namespace In {

Label::Ptr
Label::LabelNew(Identifier::PtrConst _id) {
  return new Label(_id->name());
}

} /* end of namespace In */
