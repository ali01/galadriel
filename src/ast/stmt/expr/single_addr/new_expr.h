#ifndef NEW_EXPR_H_AVR0MOFS
#define NEW_EXPR_H_AVR0MOFS

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class NamedType;
class Type;

class NewExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const NewExpr> PtrConst;
  typedef Simone::Ptr<NewExpr> Ptr;

  static Ptr NewExprNew(yyltype loc, Simone::Ptr<NamedType> class_type) {
    return new NewExpr(loc, class_type);
  }

  NewExpr(yyltype loc, Simone::Ptr<NamedType> class_type);

  /* attribute member functions */
  Simone::Ptr<const NamedType> objectType() const;
  Simone::Ptr<NamedType> objectType();

  Simone::Ptr<const Location> sizeLocation() const;
  void sizeLocationIs(Simone::Ptr<const Location> _loc);

  Simone::Ptr<const Location> vPtrLocation() const;
  void vPtrLocationIs(Simone::Ptr<const Location> _loc);

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Simone::Ptr<const Type> type() const;

  /* data members */
  Simone::Ptr<NamedType> type_;
  Simone::Ptr<const Location> size_loc_;
  Simone::Ptr<const Location> v_ptr_loc_;
};


#endif
