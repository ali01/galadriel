#ifndef SCOPE_H_35KZFJ3E
#define SCOPE_H_35KZFJ3E

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/map.h>
using Simone::Map;

/* ast includes */
#include "ast/identifier.h"
#include "ast/node.h"

/* ast/decl includes */
#include "ast/decl/decl.h"
#include "ast/decl/var_decl.h"
#include "ast/decl/fn_decl.h"
#include "ast/decl/class_decl.h"
#include "ast/decl/interface_decl.h"

/* instances obtained via factory constructor in ScopeStack class */
class Scope : public Simone::PtrInterface<Scope> {

  /* map comparison functor */
  struct IdentifierCmp {
    bool operator()(Identifier::PtrConst lhs, Identifier::PtrConst rhs) const {
      return lhs->name() < rhs->name();
    }
  };

  /* private iterator typedefs */

  typedef Map<Identifier::PtrConst,
              VarDecl::PtrConst,
              IdentifierCmp>::const_iterator const_var_decl_iter;

  typedef Map<Identifier::PtrConst,
              VarDecl::PtrConst,
              IdentifierCmp>::iterator var_decl_iter;


  typedef Map<Identifier::PtrConst,
              FnDecl::PtrConst,
              IdentifierCmp>::const_iterator const_fn_decl_iter;

  typedef Map<Identifier::PtrConst,
              FnDecl::PtrConst,
              IdentifierCmp>::iterator fn_decl_iter;


  typedef Map<Identifier::PtrConst,
              ClassDecl::PtrConst,
              IdentifierCmp>::const_iterator const_class_decl_iter;

  typedef Map<Identifier::PtrConst,
              ClassDecl::PtrConst,
              IdentifierCmp>::iterator class_decl_iter;


  typedef Map<Identifier::PtrConst,
              InterfaceDecl::PtrConst,
              IdentifierCmp>::const_iterator const_intf_decl_iter;

  typedef Map<Identifier::PtrConst,
              InterfaceDecl::PtrConst,
              IdentifierCmp>::iterator intf_decl_iter;

public:
  typedef Simone::Ptr<const Scope> PtrConst;
  typedef Simone::Ptr<Scope> Ptr;

  typedef Map<Identifier::PtrConst,
              Decl::PtrConst,
              IdentifierCmp>::const_iterator const_decl_iter;

  typedef Map<Identifier::PtrConst,
              Decl::PtrConst,
              IdentifierCmp>::iterator decl_iter;

  /* iterator support */

  const_decl_iter declsBegin() const { return decls_.begin(); }
  decl_iter declsBegin() { return decls_.begin(); }

  const_decl_iter declsEnd() const { return decls_.end(); }
  decl_iter declsEnd() { return decls_.end(); }


  /* attribute member functions */

  void declIs(Decl::Ptr _decl);
  void baseScopeIs(Scope::PtrConst _scope);

  Decl::PtrConst decl(Identifier::PtrConst _id, bool recursive=true) const;

  VarDecl::PtrConst varDecl(Identifier::PtrConst _id,
                            bool recursive=true) const;

  FnDecl::PtrConst fnDecl(Identifier::PtrConst _id, bool recursive=true) const;

  ClassDecl::PtrConst classDecl(Identifier::PtrConst _id,
                                bool recursive=true) const;

  InterfaceDecl::PtrConst interfaceDecl(Identifier::PtrConst _id,
                                        bool recursive=true) const;

  Scope::PtrConst parentScope() const { return parent_scope_; }


private:
  /* private constructor called by factory constructor in ScopeStack */
  explicit Scope(Scope::PtrConst _parent_scope);

  ~Scope() {}

  /* double dispatch */
  class NodeFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<const NodeFunctor> PtrConst;
      typedef Simone::Ptr<NodeFunctor> Ptr;

      static Ptr NodeFunctorNew(Scope::Ptr _s) {
        return new NodeFunctor(_s);
      }

      void operator()(VarDecl *_d) { scope_->varDeclIs(_d); }
      void operator()(FnDecl *_d) { scope_->fnDeclIs(_d); }
      void operator()(ClassDecl *_d) { scope_->classDeclIs(_d); }
      void operator()(InterfaceDecl *_d) { scope_->interfaceDeclIs(_d); }

    private:
      NodeFunctor(Scope::Ptr _s) : scope_(_s) {}
      
      /* data members */
      Scope::Ptr scope_;
  };

  /* private member functions */
  void varDeclIs(VarDecl::PtrConst _decl);
  void fnDeclIs(FnDecl::PtrConst _decl);
  void classDeclIs(ClassDecl::PtrConst _decl);
  void interfaceDeclIs(InterfaceDecl::PtrConst _decl);

  /* data members */
  Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCmp> decls_;
  Map<Identifier::PtrConst,VarDecl::PtrConst,IdentifierCmp> var_decls_;
  Map<Identifier::PtrConst,FnDecl::PtrConst,IdentifierCmp> fn_decls_;
  Map<Identifier::PtrConst,ClassDecl::PtrConst,IdentifierCmp> class_decls_;
  Map<Identifier::PtrConst,InterfaceDecl::PtrConst,IdentifierCmp> intf_decls_;

  Scope::PtrConst parent_scope_;

  NodeFunctor::Ptr node_functor_;

  /* operations disallowed */
  Scope(const Scope&);
  void operator=(const Scope&);

  /* friends */
  friend class ScopeStack;
};

#endif
