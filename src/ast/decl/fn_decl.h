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

  static Ptr FnDeclNew(Identifier::Ptr name,
                       Type::Ptr return_type,
                       Deque<VarDecl::Ptr>::Ptr formals) {
    return new FnDecl(name, return_type, formals);
  }

  FnDecl(Identifier::Ptr name,
         Type::Ptr returnType,
         Deque<VarDecl::Ptr>::Ptr formals);

  void SetFunctionBody(Simone::Ptr<StmtBlock> b);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Deque<VarDecl::Ptr>::Ptr formals;
  Type::Ptr _returnType;
  Simone::Ptr<StmtBlock> body;
};

#endif
