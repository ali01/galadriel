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

class Node {
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
    virtual void operator()(const Program *) {}
    virtual void operator()(const Identifier *) {}
    virtual void operator()(const Operator *) {}


    /* -- decl -- */

    virtual void operator()(const Decl *) { ABORT(); }
    virtual void operator()(const FnDecl *) {}
    virtual void operator()(const VarDecl *) {}

    /* decl/object */
    virtual void operator()(const ObjectDecl *) { ABORT(); }
    virtual void operator()(const ClassDecl *) {}
    virtual void operator()(const InterfaceDecl *) {}


    /* -- stmt -- */

    virtual void operator()(const Stmt *) { ABORT(); }
    virtual void operator()(const BreakStmt *) {}
    virtual void operator()(const PrintStmt *) {}
    virtual void operator()(const ReturnStmt *) {}
    virtual void operator()(const StmtBlock *) {}

    /* stmt/conditional */
    virtual void operator()(const ConditionalStmt *) { ABORT(); }
    virtual void operator()(const IfStmt *) {}

    /* stmt/conditional/loop */
    virtual void operator()(const LoopStmt *) { ABORT(); }
    virtual void operator()(const ForStmt *) {}
    virtual void operator()(const WhileStmt *) {}

    /* stmt/expr */
    virtual void operator()(const Expr *) { ABORT(); }
    virtual void operator()(const AssignExpr *) {}
    virtual void operator()(const CallExpr *) {}
    virtual void operator()(const EmptyExpr *) {}
    virtual void operator()(const NullExpr *) {}

    /* stmt/expr/single_addr */
    virtual void operator()(const SingleAddrExpr *) { ABORT(); }
    virtual void operator()(const BoolConstExpr *) {}
    virtual void operator()(const IntConstExpr *) {}
    virtual void operator()(const DblConstExpr *) {}
    virtual void operator()(const StrConstExpr *) {}
    virtual void operator()(const NewExpr *) {}
    virtual void operator()(const NewArrayExpr *) {}
    virtual void operator()(const ReadLineExpr *) {}

    /* stmt/expr/single_addr/compound */
    virtual void operator()(const CompoundExpr *) { ABORT(); }
    virtual void operator()(const ArithmeticExpr *) {}
    virtual void operator()(const EqualityExpr *) {}
    virtual void operator()(const LogicalExpr *) {}
    virtual void operator()(const RelationalExpr *) {}
    virtual void operator()(const PostfixExpr *) {}

    /* stmt/expr/single_addr/l_value */
    virtual void operator()(const LValueExpr *) {}
    virtual void operator()(const ArrayAccessExpr *) {}

    /* stmt/expr/single_addr/l_value/field_access */
    virtual void operator()(const FieldAccessExpr *) {}
    virtual void operator()(const ThisExpr *) {}

    /* stmt/switch */
    virtual void operator()(const SwitchStmt *) {}
    virtual void operator()(const SwitchCaseStmt *) {}


    /* -- type -- */

    virtual void operator()(const Type *) { ABORT(); }
    virtual void operator()(const VoidType *) {}
    virtual void operator()(const NullType *) {}
    virtual void operator()(const ArrayType *) {}
    virtual void operator()(const ErrorType *) {}

    /* type/named */
    virtual void operator()(const NamedType *) { ABORT(); }
    virtual void operator()(const ClassType *) {}
    virtual void operator()(const InterfaceType *) {}
  };

protected:
  /* data members */
  yyltype *location;
};

#endif
