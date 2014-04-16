#include "location.h"

Location::Location(Segment _segment, Offset _offset, const string& _name) :
  segment_(_segment), offset_(_offset), name_(_name), secondary_offset_(0) {}

Location::Location(const Location& _o) :
  segment_(_o.segment_),
  offset_(_o.offset_),
  name_(_o.name_),
  secondary_offset_(_o.secondary_offset_) {}

const string&
Location::name() const {
  return name_;
}

bool
Location::operator==(const Location& _other) const {
  if (this == &_other)
    return true;

  if (this->name() != _other.name())
    return false;

  if (this->segment() != _other.segment())
    return false;

  if (this->offset() != _other.offset())
    return false;

  return true;
}
