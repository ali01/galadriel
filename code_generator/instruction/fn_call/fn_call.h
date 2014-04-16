#ifndef FN_CALL_H_P5VGGDFL
#define FN_CALL_H_P5VGGDFL

/* code_generator/instruction includes */
#include "../instruction.h"

/* forward declarations */
class Location;

namespace In {

class FnCall : public Instruction {
public:
  typedef Simone::Ptr<const FnCall> PtrConst;
  typedef Simone::Ptr<FnCall> Ptr;

  /* attribute member functions */
  Simone::Ptr<Location> returnLocation();
  Simone::Ptr<Location> returnLocation() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  FnCall(Simone::Ptr<Location> _ret_loc);

  /* data members */
  Simone::Ptr<Location> ret_loc_;

private:
  /* operations disallowed */
  FnCall(const FnCall&);
  void operator=(const FnCall&);
};

} /* end of namespace In */

#endif
