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
FnDecl::FnDeclNew(Identifier::Ptr name, Type::Ptr return_type,
                  Deque<VarDecl::Ptr>::Ptr formals) {
  if (formals == NULL)
    formals = Deque<VarDecl::Ptr>::DequeNew();

  return new FnDecl(name, return_type, formals);
}

FnDecl::FnDecl(Identifier::Ptr name, Type::Ptr return_type,
               Deque<VarDecl::Ptr>::Ptr formals) :
  Decl(name), formals_(formals), return_type_(return_type)
{
  assert(return_type != NULL);
  assert(formals != NULL);
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

bool
FnDecl::operator==(const FnDecl& _o) const {
  if (*return_type_ != *_o.return_type_)
    return false;

  if (formals_->size() != _o.formals_->size())
    return false;

  Type::PtrConst lhs_type, rhs_type;
  for (int i = 0; i < formals_->size(); ++i) {
    lhs_type = (*formals_)[i]->type();
    rhs_type = (*_o.formals_)[i]->type();
    if (*lhs_type != *rhs_type)
      return false;
  }

  return true;
}
