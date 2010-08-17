#ifndef AST_FWD_DECLARATIONS_H_6NJ8MN3J
#define AST_FWD_DECLARATIONS_H_6NJ8MN3J

/* top level */
class Node;
class Program;
class Identifier;
class Operator;


/* decl */
class Decl;
class VarDecl;
class FnDecl;

/* decl/object */
class ObjectDecl;
class ClassDecl;
class InterfaceDecl;

/* stmt */
class Stmt;
class StmtBlock;
class PrintStmt;
class ReturnStmt;
class BreakStmt;

/* stmt/conditional */
class ConditionalStmt;
class IfStmt;

/* stmt/conditional/loop */
class LoopStmt;
class ForStmt;
class WhileStmt;

/* stmt/expr */
class Expr;
class AssignExpr;
class EmptyExpr;
class ThisExpr;

/* stmt/expr/l_value */
class LValueExpr;
class VarAccessExpr;
class ArrayAccessExpr;
class FieldAccessExpr;

/* stmt/expr/single_addr */
class SingleAddrExpr;
class BoolConstExpr;
class IntConstExpr;
class DblConstExpr;
class StrConstExpr;
class NullConstExpr;
class ReadLineExpr;
class ReadIntegerExpr;
class NewExpr;
class NewArrayExpr;

/* stmt/expr/single_addr/call_expr */
class CallExpr;
class FunctionCallExpr;
class MethodCallExpr;

/* stmt/expr/single_addr/compound */
class CompoundExpr;
class ArithmeticExpr;
class LogicalExpr;
class RelationalExpr;

/* type */
class Type;
class NamedType;
class ArrayType;

#endif
