#ifndef PARSE_PRINTER_H_K4MF6DCP
#define PARSE_PRINTER_H_K4MF6DCP

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <ast.h>

class ParsePrinter : public Simone::PtrInterface<ParsePrinter> {
public:
  typedef Simone::Ptr<const ParsePrinter> PtrConst;
  typedef Simone::Ptr<ParsePrinter> Ptr;

  static Ptr ParsePrinterNew(Program::Ptr _program) {
    return new ParsePrinter(_program);
  }

  class NodeFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<Functor> Ptr;
      typedef Simone::Ptr<const Functor> PtrConst;

      /* -- top level -- */

      void operator()(const Program *) {}
      void operator()(const Identifier *) {}
      void operator()(const Operator *) {}


      /* -- decl -- */

      void operator()(const FnDecl *) {}
      void operator()(const VarDecl *) {}

      /* decl/object */
      void operator()(const ClassDecl *) {}
      void operator()(const InterfaceDecl *) {}


      /* -- stmt -- */

      void operator()(const BreakStmt *) {}
      void operator()(const PrintStmt *) {}
      void operator()(const ReturnStmt *) {}
      void operator()(const StmtBlock *) {}

      /* stmt/conditional */
      void operator()(const IfStmt *) {}

      /* stmt/conditional/loop */
      void operator()(const ForStmt *) {}
      void operator()(const WhileStmt *) {}

      /* stmt/expr */
      void operator()(const AssignExpr *) {}
      void operator()(const CallExpr *) {}
      void operator()(const EmptyExpr *) {}
      void operator()(const NullExpr *) {}

      /* stmt/expr/single_addr */
      void operator()(const BoolConstExpr *) {}
      void operator()(const IntConstExpr *) {}
      void operator()(const DblConstExpr *) {}
      void operator()(const StrConstExpr *) {}
      void operator()(const NewExpr *) {}
      void operator()(const NewArrayExpr *) {}
      void operator()(const ReadLineExpr *) {}

      /* stmt/expr/single_addr/compound */
      void operator()(const ArithmeticExpr *) {}
      void operator()(const EqualityExpr *) {}
      void operator()(const LogicalExpr *) {}
      void operator()(const RelationalExpr *) {}
      void operator()(const PostfixExpr *) {}

      /* stmt/expr/single_addr/l_value */
      void operator()(const ArrayAccessExpr *) {}

      /* stmt/expr/single_addr/l_value/field_access */
      void operator()(const FieldAccessExpr *) {}
      void operator()(const ThisExpr *) {}

      /* stmt/switch */
      void operator()(const SwitchStmt *) {}
      void operator()(const SwitchCaseStmt *) {}


      /* -- type -- */

      void operator()(const Type *) {}
      void operator()(const NamedType *) {}
  };

private:
  ParsePrinter(Program::Ptr _program) {}
};

#endif
