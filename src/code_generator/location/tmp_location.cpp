#include "tmp_location.h"

/* stl includes */
#include <sstream>
using std::stringstream;

uint32_t TmpLocation::temp_num_ = 0;

TmpLocation::PtrConst
TmpLocation::TmpLocationNew(Offset _offset) {
  stringstream temp_num_out;
  temp_num_out << temp_num_;

  string name = "_tmp" + temp_num_out.str();
  TmpLocation::PtrConst loc = new TmpLocation(_offset, name);
  temp_num_++;

  return loc;
}

TmpLocation::TmpLocation(Offset _offset, const string& _name) :
  Location::Location(kStack, _offset, _name), is_reference_(false) {}
