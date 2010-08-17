#ifndef THIS_H_AWIFBXRQ
#define THIS_H_AWIFBXRQ

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/l_value includes */
#include "expr.h"

/* forward declarations */
class Scope;

class ThisExpr : public Expr {
public:
  typedef Simone::Ptr<const ThisExpr> PtrConst;
  typedef Simone::Ptr<ThisExpr> Ptr;

  static Ptr ThisExprNew(Node::Ptr _parent, Simone::Ptr<Scope> _scope);

  static Ptr ThisExprNew(yyltype loc) {
    return new ThisExpr(loc);
  }

  ThisExpr(yyltype loc) : Expr(loc) {}

  Simone::Ptr<const Type> type() const;
  Simone::Ptr<Location> location() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
