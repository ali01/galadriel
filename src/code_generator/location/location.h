#ifndef LOCATION_H_YQL62OVV
#define LOCATION_H_YQL62OVV

/* stl includes */
#include <iostream>
using std::ostream;

/* simone includes */
#include <simone/ptr_interface.h>

// TODO: think about making Locations immutable
class Location : public Simone::PtrInterface<Location> {
public:
  typedef Simone::Ptr<const Location> PtrConst;
  typedef Simone::Ptr<Location> Ptr;

  typedef int Offset;
  enum Segment { kStack, kData, kHeap }; // TODO: think about kHeap

  /* attribute member functions */
  const string& name() const;
  Segment segment() const { return segment_; }
  Offset offset() const { return offset_; }

  Offset secondaryOffset() const { return secondary_offset_; }
  void secondaryOffsetIs(Offset _off) { secondary_offset_ = _off; }

  bool operator==(const Location& _other);

protected:
  Location(Segment _segment, Offset _offset, const string& _name);

  /* data members */
  Segment segment_;
  Offset offset_;
  Offset secondary_offset_;
  string name_;

  /* disallowed operations */
  Location(const Location&);
  void operator=(const Location&);
};

#endif
