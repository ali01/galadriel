#ifndef VAR_ACCESS_EXPR_H_YIYU8HUJ
#define VAR_ACCESS_EXPR_H_YIYU8HUJ

/* simone includes */
#include <simone/ptr_interface.h>

/* local includes */
#include "l_value_expr.h"

/* forward declarations */
class Identifier;
class Type;
class VarDecl;

/* TODO: think about making VarAccessExpr and FieldAccessExpr inherit from a 
   common base class */

class VarAccessExpr : public LValueExpr {
public:
  typedef Simone::Ptr<const VarAccessExpr> PtrConst;
  typedef Simone::Ptr<VarAccessExpr> Ptr;

  static Ptr VarAccessExprNew(Simone::Ptr<Identifier> _id) {
    return new VarAccessExpr(_id);
  }

  VarAccessExpr(Simone::Ptr<Identifier> _id);

  /* attribute member functions */
  Simone::Ptr<const Identifier> identifier() const;
  Simone::Ptr<Identifier> identifier();
  Simone::Ptr<const Type> type() const;

  Simone::Ptr<const VarDecl> varDecl() const;
  Simone::Ptr<Location> location();

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Simone::Ptr<Identifier> identifier_;
};

#endif
