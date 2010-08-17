#ifndef LOCATION_H_YQL62OVV
#define LOCATION_H_YQL62OVV

/* stl includes */
#include <iostream>
using std::ostream;

/* simone includes */
#include <simone/ptr_interface.h>

class Location : public Simone::PtrInterface<Location> {
public:
  typedef Simone::Ptr<Location> Ptr;

  typedef int Offset;
  enum Segment { kStack, kData, kHeap };

  static Ptr LocationNew(Segment _seg, Offset _off, const string& _name) {
    return new Location(_seg, _off, _name);
  }

  static Ptr LocationNew(Location::Ptr _o) {
    return new Location(*_o);
  }

  /* attribute member functions */
  const string& name() const;
  Segment segment() const { return segment_; }
  Offset offset() const { return offset_; }

  Offset secondaryOffset() const { return secondary_offset_; }
  void secondaryOffsetIs(Offset _off) { secondary_offset_ = _off; }

  virtual bool reference() const { return false; }

  bool operator==(const Location& _other) const;

protected:
  Location(Segment _segment, Offset _offset, const string& _name);
  Location(const Location& _o);

  /* data members */
  Segment segment_;
  Offset offset_;
  string name_;

  Offset secondary_offset_;
};

#endif
