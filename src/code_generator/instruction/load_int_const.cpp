#include "load_int_const.h"

/* code_generator includes */
#include "../location.h"

LoadIntConst::Ptr
LoadIntConst::LoadIntConstNew(Location::PtrConst _loc, int _val) {
  return new LoadIntConst(_loc, _val);
}

LoadIntConst::LoadIntConst(Location::PtrConst _loc, int _val) :
                           location_(_loc), value_(_val) {
  assert(location_ != NULL);
}

Location::PtrConst
LoadIntConst::location() const {
  return location_;
}