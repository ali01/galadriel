#include "tmp_location.h"

uint32_t TmpLocation::temp_num_ = 0;

TmpLocation::PtrConst
TmpLocation::TmpLocationNew(Offset _offset) {
  string name = "_tmp" + temp_num_++;
  return new TmpLocation(_offset, name);
}

TmpLocation::TmpLocation(Offset _offset, const string& _name) :
  Location::Location(kStack, _offset, _name) {}
