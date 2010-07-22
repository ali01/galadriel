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

    virtual void operator()(const Node *) { ABORT(); }
    virtual void operator()(const Program *) = 0;
    virtual void operator()(const Identifier *) = 0;
    virtual void operator()(const Operator *) = 0;


    /* -- decl -- */

    virtual void operator()(const Decl *) { ABORT(); }
    virtual void operator()(const FnDecl *) = 0;
    virtual void operator()(const VarDecl *) = 0;

    /* decl/object */
    virtual void operator()(const ObjectDecl *) { ABORT(); }
    virtual void operator()(const ClassDecl *) = 0;
    virtual void operator()(const InterfaceDecl *) = 0;


    /* -- stmt -- */

    virtual void operator()(const Stmt *) { ABORT(); }
    virtual void operator()(const BreakStmt *) = 0;
    virtual void operator()(const PrintStmt *) = 0;
    virtual void operator()(const ReturnStmt *) = 0;
    virtual void operator()(const StmtBlock *) = 0;

    /* stmt/conditional */
    virtual void operator()(const ConditionalStmt *) { ABORT(); }
    virtual void operator()(const IfStmt *) = 0;

    /* stmt/conditional/loop */
    virtual void operator()(const LoopStmt *) { ABORT(); }
    virtual void operator()(const ForStmt *) = 0;
    virtual void operator()(const WhileStmt *) = 0;

    /* stmt/expr */
    virtual void operator()(const Expr *) { ABORT(); }
    virtual void operator()(const AssignExpr *) = 0;
    virtual void operator()(const CallExpr *) = 0;
    virtual void operator()(const EmptyExpr *) = 0;
    virtual void operator()(const NullExpr *) = 0;

    /* stmt/expr/single_addr */
    virtual void operator()(const SingleAddrExpr *) { ABORT(); }
    virtual void operator()(const BoolConstExpr *) = 0;
    virtual void operator()(const IntConstExpr *) = 0;
    virtual void operator()(const DblConstExpr *) = 0;
    virtual void operator()(const StrConstExpr *) = 0;
    virtual void operator()(const NewExpr *) = 0;
    virtual void operator()(const NewArrayExpr *) = 0;
    virtual void operator()(const ReadLineExpr *) = 0;

    /* stmt/expr/single_addr/compound */
    virtual void operator()(const CompoundExpr *) { ABORT(); }
    virtual void operator()(const ArithmeticExpr *) = 0;
    virtual void operator()(const EqualityExpr *) = 0;
    virtual void operator()(const LogicalExpr *) = 0;
    virtual void operator()(const RelationalExpr *) = 0;
    virtual void operator()(const PostfixExpr *) = 0;

    /* stmt/expr/single_addr/l_value */
    virtual void operator()(const LValueExpr *) { ABORT(); }
    virtual void operator()(const ArrayAccessExpr *) = 0;

    /* stmt/expr/single_addr/l_value/field_access */
    virtual void operator()(const FieldAccessExpr *) = 0;
    virtual void operator()(const ThisExpr *) = 0;

    /* stmt/switch */
    virtual void operator()(const SwitchStmt *) = 0;
    virtual void operator()(const SwitchCaseStmt *) = 0;


    /* -- type -- */

    virtual void operator()(const Type *) = 0;

    /* type/named */
    virtual void operator()(const NamedType *) = 0;
  };


  /* -- pure virtual interface -- */

  /* support for double dispatch */
  virtual void apply(Functor::Ptr _functor) = 0;

protected:
  /* data members */
  yyltype *location;
};

#endif
