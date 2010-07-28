#include "fn_decl.h"

/* ast includes */
#include "../identifier.h"

/* ast/decl includes */
#include "decl.h"
#include "var_decl.h"

/* ast/stmt includes */
#include "../stmt/stmt_block.h"

/* ast/type includes */
#include "../type/type.h"

FnDecl::Ptr
FnDecl::FnDeclNew(Identifier::Ptr name,
                  Type::Ptr return_type,
                  Deque<VarDecl::Ptr>::Ptr formals) {
  return new FnDecl(name, return_type, formals);
}

FnDecl::FnDecl(Identifier::Ptr n, Type::Ptr r,
               Deque<VarDecl::Ptr>::Ptr d) : Decl(n) {
  assert(n != NULL && r!= NULL && d != NULL);
}

void
FnDecl::bodyIs(StmtBlock::Ptr b) {
  assert(b != NULL);
  body_ = b;
}

Type::Ptr
FnDecl::returnType() const {
  return return_type_;
}

StmtBlock::Ptr
FnDecl::body() const {
  return body_;
}
