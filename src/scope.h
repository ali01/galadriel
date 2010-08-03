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

  /* private iterator typedefs */

  typedef Map<Identifier::PtrConst,
              VarDecl::Ptr,
              Identifier::less>::const_iterator const_var_decl_iter;

  typedef Map<Identifier::PtrConst,
              VarDecl::Ptr,
              Identifier::less>::iterator var_decl_iter;


  typedef Map<Identifier::PtrConst,
              FnDecl::Ptr,
              Identifier::less>::const_iterator const_fn_decl_iter;

  typedef Map<Identifier::PtrConst,
              FnDecl::Ptr,
              Identifier::less>::iterator fn_decl_iter;


  typedef Map<Identifier::PtrConst,
              ClassDecl::Ptr,
              Identifier::less>::const_iterator const_class_decl_iter;

  typedef Map<Identifier::PtrConst,
              ClassDecl::Ptr,
              Identifier::less>::iterator class_decl_iter;


  typedef Map<Identifier::PtrConst,
              InterfaceDecl::Ptr,
              Identifier::less>::const_iterator const_intf_decl_iter;

  typedef Map<Identifier::PtrConst,
              InterfaceDecl::Ptr,
              Identifier::less>::iterator intf_decl_iter;

public:
  typedef Simone::Ptr<const Scope> PtrConst;
  typedef Simone::Ptr<Scope> Ptr;

  typedef Map<Identifier::PtrConst,
              Decl::Ptr,
              Identifier::less>::const_iterator const_decl_iter;

  typedef Map<Identifier::PtrConst,
              Decl::Ptr,
              Identifier::less>::iterator decl_iter;

  /* iterator support */

  const_decl_iter declsBegin() const { return decls_.begin(); }
  decl_iter declsBegin() { return decls_.begin(); }

  const_decl_iter declsEnd() const { return decls_.end(); }
  decl_iter declsEnd() { return decls_.end(); }


  /* -- attribute member functions -- */

  void declIs(Decl::Ptr _decl);
  void baseScopeIs(Scope::PtrConst _scope);


  /* const interface */

  Decl::PtrConst decl(Identifier::PtrConst _id, bool recursive=true) const;

  VarDecl::PtrConst varDecl(Identifier::PtrConst _id,
                            bool recursive=true) const;

  FnDecl::PtrConst fnDecl(Identifier::PtrConst _id, bool recursive=true) const;

  ClassDecl::PtrConst classDecl(Identifier::PtrConst _id,
                                bool recursive=true) const;

  InterfaceDecl::PtrConst interfaceDecl(Identifier::PtrConst _id,
                                        bool recursive=true) const;

  Scope::PtrConst parentScope() const { return parent_scope_; }


  /* non-const interface */

  Decl::Ptr decl(Identifier::PtrConst _id, bool recursive=true);

  VarDecl::Ptr varDecl(Identifier::PtrConst _id, bool recursive=true);

  FnDecl::Ptr fnDecl(Identifier::PtrConst _id, bool recursive=true);

  ClassDecl::Ptr classDecl(Identifier::PtrConst _id, bool recursive=true);

  InterfaceDecl::Ptr interfaceDecl(Identifier::PtrConst _id,
                                   bool recursive=true);

  Scope::Ptr parentScope() { return parent_scope_; }

private:
  /* private constructor called by factory constructor in ScopeStack */
  explicit Scope(Scope::Ptr _parent_scope);

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
  void varDeclIs(VarDecl::Ptr _decl);
  void fnDeclIs(FnDecl::Ptr _decl);
  void classDeclIs(ClassDecl::Ptr _decl);
  void interfaceDeclIs(InterfaceDecl::Ptr _decl);

  /* data members */
  Map<Identifier::PtrConst,Decl::Ptr,Identifier::less> decls_;
  Map<Identifier::PtrConst,VarDecl::Ptr,Identifier::less> var_decls_;
  Map<Identifier::PtrConst,FnDecl::Ptr,Identifier::less> fn_decls_;
  Map<Identifier::PtrConst,ClassDecl::Ptr,Identifier::less> class_decls_;
  Map<Identifier::PtrConst,InterfaceDecl::Ptr,Identifier::less>
    intf_decls_;

  Scope::Ptr parent_scope_;

  NodeFunctor::Ptr node_functor_;

  /* operations disallowed */
  Scope(const Scope&);
  void operator=(const Scope&);

  /* friends */
  friend class ScopeStack;
};

#endif
