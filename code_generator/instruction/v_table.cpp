#include "v_table.h"

namespace In {

VTable::Ptr
VTable::VTableNew(Label::Ptr _class_label, Deque<Label::Ptr>::Ptr _fn_labels) {
  if (_fn_labels == NULL)
    _fn_labels = Deque<Label::Ptr>::DequeNew();

  return new VTable(_class_label, _fn_labels);
}

VTable::VTable(Label::Ptr _class_label, Deque<Label::Ptr>::Ptr _fn_labels) :
  class_label_(_class_label), fn_labels_(_fn_labels)
{
  assert(_class_label && _fn_labels);
}

} /* end of namespace In */
