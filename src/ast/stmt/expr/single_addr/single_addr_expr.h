#ifndef SINGLE_ADDR_EXPR_H_9A4HG6MH
#define SINGLE_ADDR_EXPR_H_9A4HG6MH

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* expr includes */
#include "../expr.h"

/* forward declarations */
class Location;


class SingleAddrExpr : public Expr {
public:
  typedef Simone::Ptr<const SingleAddrExpr> PtrConst;
  typedef Simone::Ptr<SingleAddrExpr> Ptr;

  Simone::Ptr<Location> location() const;
  void locationIs(Simone::Ptr<Location> _loc);

protected:
  SingleAddrExpr(yyltype loc);
  virtual ~SingleAddrExpr();

  Simone::Ptr<Location> location_;
};

#endif
