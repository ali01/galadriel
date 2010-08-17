#ifndef CODE_GENERATOR_H_TBNBRHRW
#define CODE_GENERATOR_H_TBNBRHRW

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast includes */
#include <ast/node.h>

/* instruction includes */
#include "instruction/instruction.h"
#include "instruction/label.h"

/* forward declarations */
class Program;
class Location;
class TACEmitFunctor;
class MIPSEmitFunctor;

class CodeGenerator : public Simone::PtrInterface<CodeGenerator> {
public:
  typedef Simone::Ptr<const CodeGenerator> PtrConst;
  typedef Simone::Ptr<CodeGenerator> Ptr;

  static Ptr CodeGeneratorNew(Simone::Ptr<Program> _program) {
    return new CodeGenerator(_program);
  }

private:
  CodeGenerator(Simone::Ptr<Program> _program);

  /* implementation of code generator using double dispatch mechanism */
  class NodeFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<const NodeFunctor> PtrConst;
      typedef Simone::Ptr<NodeFunctor> Ptr;

      typedef Deque<In::Instruction::Ptr>::const_iterator
              const_instruction_iter;

      static Ptr NodeFunctorNew() {
        return new NodeFunctor();
      }

      const_instruction_iter beginIn() const { return in_stream_.begin(); }
      const_instruction_iter endIn() const { return in_stream_.end(); }

      /* top level */
      void operator()(Program *);
      /* void operator()(Identifier *); */
      /* void operator()(Operator *); */

      /* decl */
      void operator()(Decl *);
      void operator()(VarDecl *);
      void operator()(FnDecl *);

      /* decl/object */
      void operator()(ObjectDecl *);
      void operator()(ClassDecl *);
      void operator()(InterfaceDecl *);

      /* stmt */
      /* void operator()(Stmt *); */
      void operator()(StmtBlock *);
      void operator()(PrintStmt *);
      void operator()(ReturnStmt *);
      void operator()(BreakStmt *);

      /* stmt/conditional */
      /* void operator()(ConditionalStmt *); */
      void operator()(IfStmt *);

      /* stmt/conditional/loop */
      /* void operator()(LoopStmt *); */
      void operator()(ForStmt *);
      void operator()(WhileStmt *);

      /* stmt/expr */
      /* void operator()(Expr *); */
      void operator()(AssignExpr *);
      /* void operator()(NullExpr *); */
      /* void operator()(EmptyExpr *); */

      /* stmt/expr/l_value */
      /* void operator()(LValueExpr *); */
      void operator()(VarAccessExpr *);
      void operator()(ArrayAccessExpr *);
      void operator()(FieldAccessExpr *);
      void operator()(ThisExpr *);

      /* stmt/expr/single_addr */
      /* void operator()(SingleAddrExpr *); */
      void operator()(BoolConstExpr *);
      void operator()(IntConstExpr *);
      /* void operator()(DblConstExpr *); */
      void operator()(StrConstExpr *);
      /* void operator()(ReadLineExpr *); */
      /* void operator()(ReadIntegerExpr *); */
      void operator()(NewExpr *);
      void operator()(NewArrayExpr *);

      /* stmt/expr/call_expr */
      void operator()(CallExpr *);
      void operator()(FunctionCallExpr *);
      void operator()(MethodCallExpr *);

      /* stmt/expr/single_addr/compound */
      void operator()(CompoundExpr *);
      void operator()(ArithmeticExpr *);
      void operator()(LogicalExpr *);
      void operator()(RelationalExpr *);

      /* type */
      /* void operator()(Type *); */
      void operator()(NamedType *);
      void operator()(ArrayType *);

    private:
      NodeFunctor() : label_num_(0) {}

      /* member functions */
      void process_node(Node::Ptr _nd);
      void process_instruction(In::Instruction::Ptr _in);
      void negate_logical_value(Simone::Ptr<const Location> dst, 
                                Simone::Ptr<const Location> aux);

      In::Label::Ptr labelNew();

      /* data members */
      Deque<In::Instruction::Ptr> in_stream_;
      uint32_t label_num_;
  };

  void emit_instruction_stream();

  /* data members */
  NodeFunctor::Ptr node_functor_;
  Simone::Ptr<In::Instruction::Functor> code_emit_functor_;

  /* disallowed operations */
  CodeGenerator(const CodeGenerator&);
  void operator=(const CodeGenerator&);
};

#endif
