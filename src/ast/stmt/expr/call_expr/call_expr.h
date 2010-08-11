#ifndef CALL_EXPR_H_DVGUL2VT
#define CALL_EXPR_H_DVGUL2VT

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr includes */
#include "../expr.h"

/* forward declarations */
class Identifier;
class Type;


class CallExpr : public Expr {
public:
  typedef Simone::Ptr<const CallExpr> PtrConst;
  typedef Simone::Ptr<CallExpr> Ptr;

  typedef Deque<Expr::Ptr>::const_iterator const_actuals_iter;
  typedef Deque<Expr::Ptr>::iterator actuals_iter;

  Simone::Ptr<Identifier> function();
  Simone::Ptr<const Identifier> function() const;

  const_actuals_iter actualsBegin() const { return actuals_->begin(); }
  actuals_iter actualsBegin() { return actuals_->begin(); }

  const_actuals_iter actualsEnd() const { return actuals_->end(); }
  actuals_iter actualsEnd() { return actuals_->end(); }

  size_t actualsCount() const { return actuals_->size(); }

  Simone::Ptr<const Type> type() const;

  /* pure virtual */
  virtual Simone::Ptr<const FnDecl> fnDecl() const = 0;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  CallExpr(yyltype _loc,
           Simone::Ptr<Identifier> _function,
           Deque<Expr::Ptr>::Ptr _args);

  /* data members */
  Simone::Ptr<Identifier> function_;
  Deque<Expr::Ptr>::Ptr actuals_;

private:

  /* disallowed operations */
  CallExpr(const CallExpr&);
  void operator=(const CallExpr&);
};

#endif
