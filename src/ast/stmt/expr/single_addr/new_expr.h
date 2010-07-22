#ifndef NEW_EXPR_H_AVR0MOFS
#define NEW_EXPR_H_AVR0MOFS

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class NamedType;

class NewExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const NewExpr> PtrConst;
  typedef Simone::Ptr<NewExpr> Ptr;

  static Ptr NewExprNew(yyltype loc, Simone::Ptr<NamedType> class_type) {
    return new NewExpr(loc, class_type);
  }
  

  NewExpr(yyltype loc, Simone::Ptr<NamedType> class_type);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Simone::Ptr<NamedType> type_;
};


#endif
