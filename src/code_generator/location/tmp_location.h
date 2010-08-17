#ifndef TMP_LOCATION_H_QP0Z6A0U
#define TMP_LOCATION_H_QP0Z6A0U

/* stl includes */
#include <string>
using std::string;

/* local includes */
#include "location.h"

class TmpLocation : public Location {
public:
  typedef Simone::Ptr<TmpLocation> Ptr;

  static Ptr TmpLocationNew(Offset _offset);

  /* attribute member functions */
  void referenceIs(bool _s) { is_reference_ = _s; }
  bool reference() const { return true; }

private:
  TmpLocation(Offset _offset, const string& name);

  /* data members */
  static uint32_t temp_num_;
  bool is_reference_;

  /* operations disallowed */
  TmpLocation(const TmpLocation&);
  void operator=(const TmpLocation&);
};


#endif
