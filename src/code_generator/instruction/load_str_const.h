#ifndef LOAD_STR_CONST_H_SVDHMVWK
#define LOAD_STR_CONST_H_SVDHMVWK

/* stl includes */
#include <iostream>
#include <string>
using std::string;
using std::ostream;

/* local includes */
#include "instruction.h"

/* forward declarations */
class Location;

namespace In {

class LoadStrConst : public Instruction {
public:
  typedef Simone::Ptr<const LoadStrConst> PtrConst;
  typedef Simone::Ptr<LoadStrConst> Ptr;

  static const size_t kMaxStringLength = 50;

  static Ptr LoadStrConstNew(Simone::Ptr<const Location> _dst,
                             const string& _value);

  /* attribute member functions */
  Simone::Ptr<const Location> dst();
  Simone::Ptr<const Location> dst() const;

  const string& value() const { return value_; }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  LoadStrConst(Simone::Ptr<const Location> _dst, const string& _value);

  /* data members */
  Simone::Ptr<const Location> dst_;
  string value_;

  /* operations disallowed */
  LoadStrConst(const LoadStrConst&);
  void operator=(const LoadStrConst&);
};

} /* end of namespace In */

#endif
