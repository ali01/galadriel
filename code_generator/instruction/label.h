#ifndef LABEL_H_GFDLAIMU
#define LABEL_H_GFDLAIMU

/* stl includes */
#include <string>
#include <iostream>
using std::string;
using std::iostream;

/* local includes */
#include "instruction.h"

/* forward declarations */
class Identifier;

namespace In {

class Label : public Instruction {
public:
  typedef Simone::Ptr<const Label> PtrConst;
  typedef Simone::Ptr<Label> Ptr;

  static PtrConst kPrintInt;
  static PtrConst kPrintBool;
  static PtrConst kPrintString;

  static PtrConst kAlloc;
  static PtrConst kReadLine;
  static PtrConst kReadInteger;

  static Ptr LabelNew(const string& _label) {
    return new Label(_label);
  }

  static Ptr LabelNew(Simone::Ptr<const Identifier> _id);

  /* attribute member functions */
  string str() const;
  const char *c_str() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Label(const string& _label) : label_(_label) {}

  /* data members */
  string label_;

  /* friends */
  friend ostream& operator<<(ostream& out, const Label& _label);

  /* operations disallowed */
  Label(const Label&);
  void operator=(const Label&);
};

inline ostream&
operator<<(ostream& out, const Label& _label) {
  return out << _label.label_;
}

} /* end of namespace In */

#endif
