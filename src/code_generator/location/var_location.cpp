#include "var_location.h"

/* ast includes */
#include <ast/decl/var_decl.h>

VarLocation::Ptr
VarLocation::VarLocationNew(Segment _segment, Offset _offset,
                            VarDecl::PtrConst _var_decl) {
  return new VarLocation(_segment, _offset, _var_decl);
}

VarLocation::VarLocation(Segment _segment, Offset _offset,
                         VarDecl::PtrConst _var_decl) :
  Location::Location(_segment, _offset, _var_decl->identifier()->name()) {}
