#ifndef L_VALUE_H_YX6Y3KF6
#define L_VALUE_H_YX6Y3KF6

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/singl_addr includes */
#include "../single_addr_expr.h"

class LValueExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const LValueExpr> PtrConst;
  typedef Simone::Ptr<LValueExpr> Ptr;  

protected:
  LValueExpr(yyltype loc) : SingleAddrExpr(loc) {}
};

#endif
