#ifndef VAR_DECL_H_NVQQP574
#define VAR_DECL_H_NVQQP574

/* ast/decl includes */
#include "decl.h"

/* forward declarations */
class Identifier;
class Type;

class VarDecl : public Decl {
public:
  VarDecl(Identifier *name, Type *type);

  Type *type() const { return type_; }

private:
  Type *type_;
};

#endif
