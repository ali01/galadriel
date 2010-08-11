#ifndef LOCATION_FACTORY_H_6RTIWATO
#define LOCATION_FACTORY_H_6RTIWATO

/* simone includes */
#include <simone/ptr_interface.h>

/* forward declarotions */
class Location;

class LocationFactory : public Simone::PtrInterface<LocationFactory> {
public:
  typedef Simone::Ptr<const LocationFactory> PtrConst;
  typedef Simone::Ptr<LocationFactory> Ptr;

  static Ptr LocationFactoryNew() {
    return new LocationFactory();
  }

  Simone::Ptr<const Location> locationNew();

private:
  LocationFactory();

  /* disallowed operations */
  LocationFactory(const LocationFactory&);
  void operator=(const LocationFactory&);
};

#endif
