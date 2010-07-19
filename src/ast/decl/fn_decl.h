#ifndef FN_DECL_H_8ZB9WKW6
#define FN_DECL_H_8ZB9WKW6

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast/decl includes */
#include "decl.h"

/* forward declarations */
class Identifier;
class StmtBlock;
class Type;
class VarDecl;

class FnDecl : public Decl {
public:
  FnDecl(Identifier *name, Type *returnType, Deque<VarDecl*>::Ptr *formals);

  void SetFunctionBody(StmtBlock *b);

private:
  
  /* data members */
  Deque<VarDecl*>::Ptr formals;
  Type *_returnType;
  StmtBlock *body;
};

#endif
