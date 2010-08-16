#ifndef VAR_LOCATION_H_WNFISS5D
#define VAR_LOCATION_H_WNFISS5D

/* local includes */
#include "location.h"

/* forward declarations */
class VarDecl;

class VarLocation : public Location {
public:
  typedef Simone::Ptr<const VarLocation> PtrConst;

  static PtrConst VarLocationNew(Segment _segment, Offset _offset,
                            Simone::Ptr<const VarDecl> _var_decl);

private:
  VarLocation(Segment _segment, Offset _offset,
              Simone::Ptr<const VarDecl> _var_decl);

  /* operations disallowed */
  VarLocation(const VarLocation&);
  void operator=(const VarLocation&);
};


#endif
