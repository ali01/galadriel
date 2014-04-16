#ifndef L_VALUE_H_YX6Y3KF6
#define L_VALUE_H_YX6Y3KF6

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/singl_addr includes */
#include "../expr.h"

/* forward declarations */
class Location;
class VarDecl;
class Type;

class LValueExpr : public Expr {
public:
  typedef Simone::Ptr<const LValueExpr> PtrConst;
  typedef Simone::Ptr<LValueExpr> Ptr;  

  /* attribute member functions */

  virtual Simone::Ptr<const Type> type() const;

  virtual Simone::Ptr<Location> location() const;
  void locationIs(Simone::Ptr<Location> _loc);

  Simone::Ptr<Location> auxLocation() const;
  void auxLocationIs(Simone::Ptr<Location> _loc);

  virtual Simone::Ptr<const VarDecl> varDecl() const = 0;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  LValueExpr(yyltype loc);
  
  /* data members */
  Simone::Ptr<Location> location_;
  Simone::Ptr<Location> aux_loc_;

  /* operations disallowed */
  LValueExpr(const LValueExpr&);
  void operator=(const LValueExpr&);
};

#endif
