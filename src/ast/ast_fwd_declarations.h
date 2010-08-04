#ifndef AST_FWD_DECLARATIONS_H_6NJ8MN3J
#define AST_FWD_DECLARATIONS_H_6NJ8MN3J

/* -- top level -- */

class Node;
class Program;
class Identifier;
class Operator;


/* -- decl -- */

class Decl;
class FnDecl;
class VarDecl;

/* decl/object */
class ClassDecl;
class InterfaceDecl;


/* -- stmt -- */

class Stmt;
class BreakStmt;
class PrintStmt;
class ReturnStmt;
class StmtBlock;

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
class CallExpr;
class EmptyExpr;
class NullExpr;

/* stmt/expr/single_addr */
class SingleAddrExpr;
class BoolConstExpr;
class IntConstExpr;
class DblConstExpr;
class StrConstExpr;
class NewExpr;
class NewArrayExpr;
class ReadLineExpr;

/* stmt/expr/single_addr/compound */
class CompoundExpr;
class ArithmeticExpr;
class EqualityExpr;
class LogicalExpr;
class RelationalExpr;

/* stmt/expr/single_addr/l_value */
class LValueExpr;
class ArrayAccessExpr;

/* stmt/expr/single_addr/l_value/field_access */
class FieldAccessExpr;
class ThisExpr;


/* -- type -- */

class Type;
class NamedType;
class ArrayType;

#endif
