/* File: node.h
 * -----------
 * This file defines the abstract base class Node and the concrete
 * Identifier node subclass that is used throughout the tree as
 * leaf nodes. A parse tree is a hierarchical collection of ast nodes (or,
 * more correctly, of instances of concrete subclassses such as VarDecl,
 * ForStmt, and AssignExpr).
 *
 * Location: Each node maintains its lexical location (line and columns in
 * file), that location can be NULL for those nodes that don't care/use
 * locations. The location is typcially set by the node constructor. The
 * location is used to provide the context when reporting semantic errors.
 *
 * Parent: Each node has a pointer to its parent. For a Program node, the
 * parent is NULL, for all other nodes it is the pointer to the node one level
 * up in the parse tree. The parent is not set in the constructor (during a
 * bottom-up parse we don't know the parent at the time of construction) but
 * instead we wait until assigning the children into the parent node and then
 * set up links in both directions. The parent link is typically not used
 * during parsing, but is more important in later phases.
 *
 */

#ifndef NODE_H_CU7MI57H
#define NODE_H_CU7MI57H

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/utility.h>

/* project includes */
#include <lex_location.h>

/* local includes */
#include "../ast_fwd_declarations.h"

/* forward declarations */
class Scope;
struct yyltype;

class Node : public Simone::PtrInterface<Node> {
public:
  typedef Simone::Ptr<const Node> PtrConst;
  typedef Simone::Ptr<Node> Ptr;

  yyltype *lexLoc() const { return lex_location_; }

  /* -- attribute member functions -- */

  Simone::Ptr<Scope> scope();
  Simone::Ptr<const Scope> scope() const;
  virtual void scopeIs(Simone::Ptr<Scope> _s);

  Node::Ptr parent() { return parent_; }
  Node::PtrConst parent() const { return parent_; }
  void parentIs(Node::Ptr _parent) { parent_ = _parent; }

  virtual Simone::Ptr<const ClassDecl> nearestClass() const;
  virtual Simone::Ptr<const FnDecl> nearestFunction() const;
  virtual Simone::Ptr<const LoopStmt> nearestLoop() const;

  /* support for double dispatch */
  class Functor : public Simone::PtrInterface<Functor> {
  public:
    typedef Simone::Ptr<Functor> Ptr;
    typedef Simone::Ptr<const Functor> PtrConst;

    /* top level */
    virtual void operator()(Node *) { ABORT(); }
    virtual void operator()(Program *) {}
    virtual void operator()(Identifier *) {}
    virtual void operator()(Operator *) {}

    /* decl */
    virtual void operator()(Decl *) { ABORT(); }
    virtual void operator()(VarDecl *) {}
    virtual void operator()(FnDecl *) {}

    /* decl/object */
    virtual void operator()(ObjectDecl *) { ABORT(); }
    virtual void operator()(ClassDecl *) {}
    virtual void operator()(InterfaceDecl *) {}

    /* stmt */
    virtual void operator()(Stmt *) { ABORT(); }
    virtual void operator()(StmtBlock *) {}
    virtual void operator()(PrintStmt *) {}
    virtual void operator()(ReturnStmt *) {}
    virtual void operator()(BreakStmt *) {}

    /* stmt/conditional */
    virtual void operator()(ConditionalStmt *) { ABORT(); }
    virtual void operator()(IfStmt *) {}

    /* stmt/conditional/loop */
    virtual void operator()(LoopStmt *) {}
    virtual void operator()(ForStmt *) {}
    virtual void operator()(WhileStmt *) {}

    /* stmt/expr */
    virtual void operator()(Expr *) { ABORT(); }
    virtual void operator()(AssignExpr *) {}
    virtual void operator()(NullExpr *) {}
    virtual void operator()(EmptyExpr *) {}

    /* stmt/expr/call_expr */
    virtual void operator()(CallExpr *) { ABORT(); }
    virtual void operator()(FunctionCallExpr *) {}
    virtual void operator()(MethodCallExpr *) {}

    /* stmt/expr/single_addr */
    virtual void operator()(SingleAddrExpr *) { ABORT(); }
    virtual void operator()(BoolConstExpr *) {}
    virtual void operator()(IntConstExpr *) {}
    virtual void operator()(DblConstExpr *) {}
    virtual void operator()(StrConstExpr *) {}
    virtual void operator()(ReadLineExpr *) {}
    virtual void operator()(ReadIntegerExpr *) {}
    virtual void operator()(NewExpr *) {}
    virtual void operator()(NewArrayExpr *) {}

    /* stmt/expr/single_addr/compound */
    virtual void operator()(CompoundExpr *) { ABORT(); }
    virtual void operator()(ArithmeticExpr *) {}
    virtual void operator()(LogicalExpr *) {}
    virtual void operator()(RelationalExpr *) {}

    /* stmt/expr/single_addr/l_value */
    virtual void operator()(LValueExpr *) { ABORT(); }
    virtual void operator()(VarAccessExpr *) {}
    virtual void operator()(ArrayAccessExpr *) {}
    virtual void operator()(FieldAccessExpr *) {}
    virtual void operator()(ThisExpr *) {}

    /* type */
    virtual void operator()(Type *) {}
    virtual void operator()(NamedType *) {}
    virtual void operator()(ArrayType *) {}
  };

  /* support for double dispatch */
  virtual void self_apply(Functor::Ptr _functor) = 0;

protected:
  Node(yyltype loc);
  Node();
  virtual ~Node();

  /* data members */
  yyltype *lex_location_;

  Node::Ptr parent_;
  Simone::Ptr<Scope> scope_;
};

#endif
