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
#include <lex_loc.h>

/* local includes */
#include "ast_fwd_declarations.h"

/* forward declarations */
class Decl;
class Stmt;
struct yyltype;

class Node : public Simone::PtrInterface<Node> {
public:
  Node(yyltype loc);
  Node();
  virtual ~Node() {}

  yyltype *lexLoc() const { return location; }

  /* support for double dispatch */
  class Functor : public Simone::PtrInterface<Functor> {
  public:
    typedef Simone::Ptr<Functor> Ptr;
    typedef Simone::Ptr<const Functor> PtrConst;

    /* -- top level -- */

    virtual void operator()(Node *) { ABORT(); }
    virtual void operator()(Program *) { ABORT(); }
    virtual void operator()(Identifier *) { ABORT(); }
    virtual void operator()(Operator *) { ABORT(); }


    /* -- decl -- */

    virtual void operator()(Decl *) { ABORT(); }
    virtual void operator()(FnDecl *) { ABORT(); }
    virtual void operator()(VarDecl *) { ABORT(); }

    /* decl/object */
    virtual void operator()(ObjectDecl *) { ABORT(); }
    virtual void operator()(ClassDecl *) { ABORT(); }
    virtual void operator()(InterfaceDecl *) { ABORT(); }


    /* -- stmt -- */

    virtual void operator()(Stmt *) { ABORT(); }
    virtual void operator()(BreakStmt *) { ABORT(); }
    virtual void operator()(PrintStmt *) { ABORT(); }
    virtual void operator()(ReturnStmt *) { ABORT(); }
    virtual void operator()(StmtBlock *) { ABORT(); }

    /* stmt/conditional */
    virtual void operator()(ConditionalStmt *) { ABORT(); }
    virtual void operator()(IfStmt *) { ABORT(); }

    /* stmt/conditional/loop */
    virtual void operator()(LoopStmt *) { ABORT(); }
    virtual void operator()(ForStmt *) { ABORT(); }
    virtual void operator()(WhileStmt *) { ABORT(); }

    /* stmt/expr */
    virtual void operator()(Expr *) { ABORT(); }
    virtual void operator()(AssignExpr *) { ABORT(); }
    virtual void operator()(CallExpr *) { ABORT(); }
    virtual void operator()(EmptyExpr *) { ABORT(); }
    virtual void operator()(NullExpr *) { ABORT(); }

    /* stmt/expr/single_addr */
    virtual void operator()(SingleAddrExpr *) { ABORT(); }
    virtual void operator()(BoolConstExpr *) { ABORT(); }
    virtual void operator()(IntConstExpr *) { ABORT(); }
    virtual void operator()(DblConstExpr *) { ABORT(); }
    virtual void operator()(StrConstExpr *) { ABORT(); }
    virtual void operator()(NewExpr *) { ABORT(); }
    virtual void operator()(NewArrayExpr *) { ABORT(); }
    virtual void operator()(ReadLineExpr *) { ABORT(); }

    /* stmt/expr/single_addr/compound */
    virtual void operator()(CompoundExpr *) { ABORT(); }
    virtual void operator()(ArithmeticExpr *) { ABORT(); }
    virtual void operator()(EqualityExpr *) { ABORT(); }
    virtual void operator()(LogicalExpr *) { ABORT(); }
    virtual void operator()(RelationalExpr *) { ABORT(); }
    virtual void operator()(PostfixExpr *) { ABORT(); }

    /* stmt/expr/single_addr/l_value */
    virtual void operator()(LValueExpr *) { ABORT(); }
    virtual void operator()(ArrayAccessExpr *) { ABORT(); }

    /* stmt/expr/single_addr/l_value/field_access */
    virtual void operator()(FieldAccessExpr *) { ABORT(); }
    virtual void operator()(ThisExpr *) { ABORT(); }

    /* stmt/switch */
    virtual void operator()(SwitchStmt *) { ABORT(); }
    virtual void operator()(SwitchCaseStmt *) { ABORT(); }


    /* -- type -- */

    virtual void operator()(Type *) { ABORT(); }

    /* type/named */
    virtual void operator()(NamedType *) { ABORT(); }
  };


  /* -- pure virtual interface -- */

  /* support for double dispatch */
  virtual void apply(Functor::Ptr _functor) = 0;

protected:
  /* data members */
  yyltype *location;
};

#endif
