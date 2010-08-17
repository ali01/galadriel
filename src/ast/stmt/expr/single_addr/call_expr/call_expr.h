#ifndef CALL_EXPR_H_DVGUL2VT
#define CALL_EXPR_H_DVGUL2VT

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* project includes */
#include <lex_location.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/stmt/expr includes */
#include "../single_addr_expr.h"

/* forward declarations */
class Identifier;
class Type;


class CallExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const CallExpr> PtrConst;
  typedef Simone::Ptr<CallExpr> Ptr;

  typedef Deque<Expr::Ptr>::const_iterator const_actuals_iter;
  typedef Deque<Expr::Ptr>::iterator actuals_iter;

  typedef Deque<Expr::Ptr>::const_reverse_iterator const_reverse_actuals_iter;

  Simone::Ptr<Identifier> identifier();
  Simone::Ptr<const Identifier> identifier() const;

  const_actuals_iter actualsBegin() const { return actuals_->begin(); }
  actuals_iter actualsBegin() { return actuals_->begin(); }

  const_actuals_iter actualsEnd() const { return actuals_->end(); }
  actuals_iter actualsEnd() { return actuals_->end(); }

  const_reverse_actuals_iter actualsReverseBegin() const;
  const_reverse_actuals_iter actualsReverseEnd() const;

  size_t actualsCount() const { return actuals_->size(); }

  Simone::Ptr<const Type> type() const;

  Simone::Ptr<const Location> fnLocation() const;
  void fnLocationIs(Simone::Ptr<const Location> _loc);

  /* pure virtual */
  virtual Simone::Ptr<const FnDecl> fnDecl() const = 0;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  CallExpr(yyltype _loc,
           Simone::Ptr<Identifier> _identifier,
           Deque<Expr::Ptr>::Ptr _args);

  /* data members */
  Simone::Ptr<Identifier> identifier_;
  Deque<Expr::Ptr>::Ptr actuals_;

  Simone::Ptr<const Location> fn_location_;

private:

  /* disallowed operations */
  CallExpr(const CallExpr&);
  void operator=(const CallExpr&);
};

#endif
