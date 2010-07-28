#ifndef FN_DECL_H_8ZB9WKW6
#define FN_DECL_H_8ZB9WKW6

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast/decl includes */
#include "decl.h"
#include "var_decl.h"

/* forward declarations */
class Identifier;
class StmtBlock;
class Type;

class FnDecl : public Decl {
public:
  typedef Simone::Ptr<const FnDecl> PtrConst;
  typedef Simone::Ptr<FnDecl> Ptr;
  
  typedef Deque<VarDecl::Ptr>::const_iterator const_formal_iter;
  typedef Deque<VarDecl::Ptr>::iterator formal_iter;

  static Ptr FnDeclNew(Identifier::Ptr name,
                       Simone::Ptr<Type> return_type,
                       Deque<VarDecl::Ptr>::Ptr formals);

  FnDecl(Identifier::Ptr name,
         Simone::Ptr<Type> returnType,
         Deque<VarDecl::Ptr>::Ptr formals);

  formal_iter formalsBegin() { return formals_->begin(); }
  const_formal_iter formalsBegin() const { return formals_->begin(); }

  formal_iter formalsEnd() { return formals_->end(); }
  const_formal_iter formalsEnd() const { return formals_->end(); }

  Simone::Ptr<Type> returnType() const;
  Simone::Ptr<StmtBlock> body() const;

  void bodyIs(Simone::Ptr<StmtBlock> b);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

private:
  /* data members */
  Deque<VarDecl::Ptr>::Ptr formals_;
  Simone::Ptr<Type> return_type_;
  Simone::Ptr<StmtBlock> body_;
};

#endif
