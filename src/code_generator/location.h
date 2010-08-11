#ifndef LOCATION_H_YQL62OVV
#define LOCATION_H_YQL62OVV

/* stl includes */
#include <iostream>
using std::ostream;

/* simone includes */
#include <simone/ptr_interface.h>

class Location : public Simone::PtrInterface<Location> {
public:
  typedef Simone::Ptr<const Location> PtrConst;
  typedef Simone::Ptr<Location> Ptr;

  enum Segment { kStack, kData };

  // Segment _seg, int _offset, 
  static Ptr LocationNew() {
    return new Location();
  }

protected:
  Location() {}

private:

  /* disallowed operations */
  Location(const Location&);
  void operator=(const Location&);
};

inline ostream& operator<<(ostream& out, const Location& _loc) {
  return out;
}

#endif
