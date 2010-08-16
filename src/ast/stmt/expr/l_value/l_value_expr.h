#ifndef L_VALUE_H_YX6Y3KF6
#define L_VALUE_H_YX6Y3KF6

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/singl_addr includes */
#include "../expr.h"

class LValueExpr : public Expr {
public:
  typedef Simone::Ptr<const LValueExpr> PtrConst;
  typedef Simone::Ptr<LValueExpr> Ptr;  

protected:
  LValueExpr(yyltype loc) : Expr(loc) {}
};

#endif