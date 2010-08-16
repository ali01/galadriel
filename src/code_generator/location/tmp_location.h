#ifndef TMP_LOCATION_H_QP0Z6A0U
#define TMP_LOCATION_H_QP0Z6A0U

/* stl includes */
#include <string>
using std::string;

/* local includes */
#include "location.h"

class TmpLocation : public Location {
public:
  typedef Simone::Ptr<const TmpLocation> PtrConst;

  static PtrConst TmpLocationNew(Offset _offset);

  /* attribute member functions */

private:
  TmpLocation(Offset _offset, const string& name);

  /* data members */
  static uint32_t temp_num_;

  /* operations disallowed */
  TmpLocation(const TmpLocation&);
  void operator=(const TmpLocation&);
};


#endif
