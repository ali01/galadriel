#include "var_decl.h"

/* ast includes */
#include "../identifier.h"

/* ast/type includes */
#include "../type/type.h"

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n), type_(t) {
  assert(n != NULL && t != NULL);
}
