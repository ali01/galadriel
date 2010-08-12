#ifndef V_TABLE_H_6NQGJ7PQ
#define V_TABLE_H_6NQGJ7PQ

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* local includes */
#include "instruction.h"
#include "label.h"

namespace In {

class VTable : public Instruction {
public:
  typedef Simone::Ptr<const VTable> PtrConst;
  typedef Simone::Ptr<VTable> Ptr;

  typedef Deque<Label::Ptr>::iterator label_iter;
  typedef Deque<Label::Ptr>::const_iterator const_label_iter;

  static Ptr VTableNew(Label::Ptr _class_label,
                       Deque<Label::Ptr>::Ptr _fn_labels);

  /* attribute member functions */
  Label::Ptr classLabel() { return class_label_; }
  Label::PtrConst classLabel() const { return class_label_; }

  label_iter fnLabelsBegin() { return fn_labels_->begin(); }
  const_label_iter fnLabelsBegin() const { return fn_labels_->begin(); }

  label_iter fnLabelsEnd() { return fn_labels_->end(); }
  const_label_iter fnLabelsEnd() const { return fn_labels_->end(); }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  VTable(Label::Ptr _class_label, Deque<Label::Ptr>::Ptr _fn_labels);

  /* data members */
  Label::Ptr class_label_;
  Deque<Label::Ptr>::Ptr fn_labels_;

  /* operations disallowed */
  VTable(const VTable&);
  void operator=(const VTable&);
};


} /* end of namespace In */

#endif
