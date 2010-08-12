#include "location.h"

Location::Location(Segment _segment, Offset _offset, const string& _name) :
  segment_(_segment), offset_(_offset), secondary_offset_(0), name_(_name) {}
