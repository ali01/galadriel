#ifndef CALL_H_D5Q44BY5
#define CALL_H_D5Q44BY5

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Identifier;
class Type;
class ObjectDecl;
class FnDecl;

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().    We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */

// TODO: refactor into two classes: method and function exprs

class CallExpr : public Expr {
public:
  typedef Simone::Ptr<const CallExpr> PtrConst;
  typedef Simone::Ptr<CallExpr> Ptr;

  typedef Deque<Expr::Ptr>::const_iterator const_actuals_iter;
  typedef Deque<Expr::Ptr>::iterator actuals_iter;

  static Ptr CallExprNew(yyltype _loc,
                         Expr::Ptr _base,
                         Simone::Ptr<Identifier> _function,
                         Deque<Expr::Ptr>::Ptr _args) {
    return new CallExpr(_loc, _base, _function, _args);
  }


  CallExpr(yyltype _loc,
           Expr::Ptr _base,
           Simone::Ptr<Identifier> _field,
           Deque<Expr::Ptr>::Ptr _args);

  /* attribute member functions */
  Expr::Ptr base() { return base_; }
  Expr::PtrConst base() const { return base_; }

  Simone::Ptr<Identifier> function();
  Simone::Ptr<const Identifier> function() const;

  const_actuals_iter actualsBegin() const { return actuals_->begin(); }
  actuals_iter actualsBegin() { return actuals_->begin(); }

  const_actuals_iter actualsEnd() const { return actuals_->end(); }
  actuals_iter actualsEnd() { return actuals_->end(); }

  size_t actualsCount() const { return actuals_->size(); }

  Simone::Ptr<const FnDecl> fnDecl() const;

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:

  class BaseDeclFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<const BaseDeclFunctor> PtrConst;
      typedef Simone::Ptr<BaseDeclFunctor> Ptr;

      static Ptr BaseDeclFunctorNew(CallExpr::Ptr _call_expr) {
        return new BaseDeclFunctor(_call_expr);
      }

      Simone::Ptr<ObjectDecl> baseDecl() const;

      void operator()(NamedType *);
      void operator()(ArrayType *);

    private:
      BaseDeclFunctor(CallExpr::Ptr _call_expr) : call_expr_(_call_expr) {}

      /* data members */
      Simone::Ptr<ObjectDecl> base_decl_;
      CallExpr::Ptr call_expr_;
  };

  /* data members */
  Expr::Ptr base_; /* base will be null if no explicit base */
  Simone::Ptr<Identifier> function_;
  Deque<Expr::Ptr>::Ptr actuals_;

  BaseDeclFunctor::Ptr base_decl_functor_;
};

#endif
