/* File: parser.y
 * --------------
 * Yacc input file to generate the parser for the compiler.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include <semantic_analyser/semantic_analyser.h>

/* parser includes */
#include "parser.h"
#include "scanner.h" /* for yylex */

#include "error.h"
#include "../utility.h"

/* standard error-handling routine */
void yyerror(const char *msg, yyltype *loc = NULL);

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */

/* yylval
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. */

%union {
  /* primitives */
  int int_const;
  bool bool_const;
  char *str_const;
  double dbl_const;
  char ident[kMaxIdentifierLength + 1]; /* +1 for terminating null */

  /* top level singletons */
  Type *type;
  Decl *decl;
  Stmt *stmt;
  Expr *expr;
  StmtBlock *stmt_block;

  /* decl singletons */
  VarDecl *var_decl;
  FnDecl *fn_decl;
  ClassDecl *class_decl;
  InterfaceDecl *interface_decl;
  
  /* type singletons */
  NamedType *named_type;
  
  /* stmt/expr singletons */
  LValueExpr *l_value_expr;

  /* top level lists */
  Deque<Decl::Ptr> *decl_list;
  Deque<Expr::Ptr> *expr_list;
  Deque<Stmt::Ptr> *stmt_list;

  /* other lists */
  Deque<VarDecl::Ptr> *var_decl_list;
  Deque<FnDecl::Ptr> *fn_decl_list;
  Deque<NamedType::Ptr> *named_type_list;
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Yacc will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Void T_Bool T_Int T_Double T_String T_Class
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine
%token   T_UnaryMinus

%token   <ident> T_Identifier
%token   <str_const> T_StringConstant
%token   <int_const> T_IntConstant
%token   <dbl_const> T_DoubleConstant
%token   <bool_const> T_BoolConstant


/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "decl_list" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "decl_list" which is of type List<Decl*>. */

/* stmt */
%type <stmt> Stmt ReturnStmt BreakStmt PrintStmt
%type <stmt> IfStmt WhileStmt ForStmt
%type <stmt_block> StmtBlock

/* decl */
%type <decl> Decl Field
%type <var_decl> VariableDecl Variable
%type <fn_decl> FunctionDecl Prototype
%type <class_decl> ClassDecl
%type <interface_decl> InterfaceDecl

/* expr */
%type <expr> Expr Constant Call ExprOrEmpty
%type <l_value_expr> LValue

/* type */
%type <type> Type
%type <named_type> Extends;

/* top level lists */
%type <stmt_list> StmtList
%type <expr_list> Actuals ExprList
%type <decl_list> DeclList FieldList

/* other lists */
%type <var_decl_list> VariableList VariableDeclList Formals
%type <fn_decl_list> PrototypeList
%type <named_type_list> Implements Protocol



/* -- conflict resolution -- */

%left T_SimpleIfStmt
%left T_Else


/* operator precedence */

%left '='
%left T_Or
%left T_And
%nonassoc T_Equal T_NotEqual
%nonassoc '<' T_LessEqual '>' T_GreaterEqual
%left '+' '-'
%left '*' '/' '%'
%right T_UnaryMinus '!'
%left '[' '.'


%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section. */
 
Program           : DeclList {
                      Program::Ptr program = Program::ProgramNew($1);
                      // TODO: if(parse errors)
                      SemanticAnalyser::Ptr semantic_analyser =
                        SemanticAnalyser::SemanticAnalyserNew(program);
                    }
                  ;

DeclList          : DeclList Decl {
                      $$ = $1;
                      $$->pushBack($2);
                    }
                  | Decl {
                      $$ = new Deque<Decl::Ptr>();
                      $$->pushBack($1);
                    }
                  ;

Decl              : VariableDecl   { $$ = $1; }
                  | FunctionDecl   { $$ = $1; }
                  | ClassDecl      { $$ = $1; }
                  | InterfaceDecl  { $$ = $1; }
                  ;

VariableDecl      : Variable ';'   { $$ = $1; }
                  ;

Variable          : Type T_Identifier {
                      Identifier::Ptr ident;
                      ident = Identifier::IdentifierNew(@2, $2);
                      $$ = new VarDecl(ident, $1);
                    }
                  ;

Type              : T_Int        { $$ = Type::kInt.ptr();  }
                  | T_Double     { $$ = Type::kDouble.ptr();  }
                  | T_Bool       { $$ = Type::kBool.ptr(); }
                  | T_String     { $$ = Type::kString.ptr();  }
                  | Type T_Dims  { $$ = new ArrayType(@1, $1); }
                  | T_Identifier {
                      Identifier::Ptr ident;
                      ident = Identifier::IdentifierNew(@1, $1);
                      $$ = new NamedType(ident);
                    }
                  ;

FunctionDecl      : Type T_Identifier '(' Formals ')' StmtBlock {
                      Identifier::Ptr name;
                      name = Identifier::IdentifierNew(@2, $2);

                      FnDecl *fn = new FnDecl(name, $1, $4);
                      fn->bodyIs($6);
                      $$ = fn;
                    }
                  | T_Void T_Identifier '(' Formals ')' StmtBlock {
                      Identifier::Ptr name;
                      name = Identifier::IdentifierNew(@2, $2);

                      $$ = new FnDecl(name, Type::kVoid, $4);
                      $$->bodyIs($6);
                    }
                  ;

Formals           : VariableList { $$ = $1; }
                  | /* empty */  { $$ = new Deque<VarDecl::Ptr>(); }
                  ;

VariableDeclList  : VariableDeclList VariableDecl {
                      $$ = $1;
                      $$->pushBack($2);
                    }
                  | VariableDecl {
                      $$ = new Deque<VarDecl::Ptr>();
                      $$->pushBack($1);
                    }
                  ;

VariableList      : VariableList ',' Variable {
                      $$ = $1;
                      $$->pushBack($3);
                    }
                  | Variable {
                      $$ = new Deque<VarDecl::Ptr>();
                      $$->pushBack($1);
                    }
                  ;

ClassDecl         : T_Class T_Identifier Extends Implements '{' FieldList '}' {
                      Identifier::Ptr name = Identifier::IdentifierNew(@2, $2);
                      $$ = new ClassDecl(name, $3, $4, $6);
                    }
                  | T_Class T_Identifier Extends Implements '{' '}' {
                      Identifier::Ptr name = Identifier::IdentifierNew(@2, $2);
                      Deque<Decl::Ptr> *decl_list = new Deque<Decl::Ptr>();
                      // TODO: consider if decl_list should be NULL
                      $$ = new ClassDecl(name, $3, $4, decl_list);
                    }
                  ;

Extends           : T_Extends T_Identifier {
                      Identifier::Ptr name = Identifier::IdentifierNew(@2, $2);
                      $$ = new NamedType(name);
                    }
                  | /* empty */ { $$ = NULL; }
                  ;

Implements        : T_Implements Protocol { $$ = $2; }
                  | /* empty */ { $$ = new Deque<NamedType::Ptr>(); }
                  ;

Protocol          : Protocol ',' T_Identifier {
                      Identifier::Ptr name = Identifier::IdentifierNew(@3, $3);
                      NamedType::Ptr type = NamedType::NamedTypeNew(name);

                      $$ = $1;
                      $$->pushBack(type);
                    }
                  | T_Identifier {
                      Identifier::Ptr name = Identifier::IdentifierNew(@1, $1);
                      NamedType::Ptr type = NamedType::NamedTypeNew(name);
                      $$ = new Deque<NamedType::Ptr>();
                      $$->pushBack(type);
                    }
                  ;

FieldList         : FieldList Field {
                      $$ = $1;
                      $$->pushBack($2);
                    }
                  | Field {
                      $$ = new Deque<Decl::Ptr>();
                      $$->pushBack($1);
                    }
                  ;

Field             : VariableDecl { $$ = $1; }
                  | FunctionDecl { $$ = $1; }
                  ;

InterfaceDecl     : T_Interface T_Identifier '{' PrototypeList '}' {
                      Identifier::Ptr name = Identifier::IdentifierNew(@2, $2);
                      $$ = new InterfaceDecl(name, $4);
                    }
                  | T_Interface T_Identifier '{' '}' {
                      Identifier::Ptr name = Identifier::IdentifierNew(@2, $2);
                      Deque<FnDecl::Ptr>::Ptr decl_list;
                      decl_list = new Deque<FnDecl::Ptr>();
                      $$ = new InterfaceDecl(name, decl_list);
                    }
                  ;

PrototypeList     : PrototypeList Prototype {
                      $$ = $1;
                      $$->pushBack($2);
                    }
                  | Prototype {
                      $$ = new Deque<FnDecl::Ptr>();
                      $$->pushBack($1);
                    }
                  ;

Prototype         : Type T_Identifier '(' Formals ')' ';' {
                      Identifier::Ptr name = Identifier::IdentifierNew(@2, $2);
                      $$ = new FnDecl(name, $1, $4);
                    }
                  | T_Void T_Identifier '(' Formals ')' ';' {
                      Identifier::Ptr name = Identifier::IdentifierNew(@2, $2);
                      $$ = new FnDecl(name, Type::kVoid, $4);
                    }
                  ;


/* statements */

StmtBlock         : '{' VariableDeclList StmtList '}' {
                      $$ = new StmtBlock($2, $3);
                    }
                  | '{' VariableDeclList '}' {
                      Deque<Stmt::Ptr>::Ptr stmt_list = new Deque<Stmt::Ptr>();
                      $$ = new StmtBlock($2, stmt_list);
                    }
                  | '{' StmtList '}' {
                      Deque<VarDecl::Ptr>::Ptr var_decl_list;
                      var_decl_list = new Deque<VarDecl::Ptr>();

                      $$ = new StmtBlock(var_decl_list, $2);
                    }
                  | '{' '}' {
                      Deque<VarDecl::Ptr>::Ptr var_decl_list;
                      var_decl_list = new Deque<VarDecl::Ptr>();

                      Deque<Stmt::Ptr>::Ptr stmt_list = new Deque<Stmt::Ptr>();

                      $$ = new StmtBlock(var_decl_list, stmt_list);
                    }
                  ;

Stmt              : ExprOrEmpty ';' { $$ = $1; }
                  | IfStmt          { $$ = $1; }
                  | WhileStmt       { $$ = $1; }
                  | ForStmt         { $$ = $1; }
                  | BreakStmt       { $$ = $1; }
                  | ReturnStmt      { $$ = $1; }
                  | PrintStmt       { $$ = $1; }
                  | StmtBlock       { $$ = $1; }
                  ;

StmtList          : StmtList Stmt {
                      $$ = $1;
                      $$->pushBack($2);
                    }
                  | Stmt {
                      $$ = new Deque<Stmt::Ptr>();
                      $$->pushBack($1);
                    }
                  ;

IfStmt            : T_If '(' Expr ')' Stmt %prec T_SimpleIfStmt {
                      $$ = new IfStmt($3, $5, NULL);
                    }
                  | T_If '(' Expr ')' Stmt T_Else Stmt {
                      $$ = new IfStmt($3, $5, $7);
                    }
                  ;

WhileStmt         : T_While '(' Expr ')' Stmt { $$ = new WhileStmt($3, $5); }
                  ;

ForStmt           : T_For '(' ExprOrEmpty ';' Expr';' ExprOrEmpty ')' Stmt {
                      $$ = new ForStmt($3, $5, $7, $9);
                    }
                  ;

ReturnStmt        : T_Return ExprOrEmpty ';' {
                      $$ = new ReturnStmt(Join(@1, @3), $2);
                    }
                  ;

BreakStmt         : T_Break ';' { $$ = new BreakStmt(Join(@1, @2)); }
                  ;

PrintStmt         : T_Print '(' ExprList ')' ';' { $$ = new PrintStmt($3); }
                  ;

ExprOrEmpty       : Expr        { $$ = $1; }
                  | /* empty */ { $$ = new EmptyExpr(); }
                  ;


/* expressions */

ExprList          : ExprList ',' Expr {
                      $$ = $1;
                      $$->pushBack($3);
                    }
                  | Expr {
                      $$ = new Deque<Expr::Ptr>();
                      $$->pushBack($1);
                    }
                  ;

Expr              : LValue '=' Expr  { $$ = new AssignExpr($1, $3); }
                  | Constant         { $$ = $1; }
                  | LValue           { $$ = $1; }
                  | Call             { $$ = $1; }
                  | '(' Expr ')'     { $$ = $2; }
                  | Expr '+' Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "+");
                      $$ = new ArithmeticExpr($1, op, $3);
                    }
                  | Expr '-' Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "-");
                      $$ = new ArithmeticExpr($1, op, $3);
                    }
                  | Expr '*' Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "*");
                      $$ = new ArithmeticExpr($1, op, $3);
                    }
                  | Expr '/' Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "/");
                      $$ = new ArithmeticExpr($1, op, $3);
                    }
                  | Expr '%' Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "%");
                      $$ = new ArithmeticExpr($1, op, $3);
                    }
                  | '-' Expr  %prec T_UnaryMinus {
                      Operator::Ptr op = Operator::OperatorNew(@1, "-");
                      $$ = new ArithmeticExpr(op, $2);
                    }
                  | Expr '<' Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "<");
                      $$ = new RelationalExpr($1, op, $3);
                    }
                  | Expr T_LessEqual Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "<=");
                      $$ = new RelationalExpr($1, op, $3);
                    }
                  | Expr '>' Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, ">");
                      $$ = new RelationalExpr($1, op, $3);
                    }
                  | Expr T_GreaterEqual Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, ">=");
                      $$ = new RelationalExpr($1, op, $3);
                    }
                  | Expr T_Equal Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "==");
                      $$ = new RelationalExpr($1, op, $3);
                    }
                  | Expr T_NotEqual Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "!=");
                      $$ = new RelationalExpr($1, op, $3);
                    }
                  | Expr T_And Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "&&");
                      $$ = new LogicalExpr($1, op, $3);
                    }
                  | Expr T_Or Expr {
                      Operator::Ptr op = Operator::OperatorNew(@2, "||");
                      $$ = new LogicalExpr($1, op, $3);
                    }
                  | '!' Expr {
                        Operator::Ptr op = Operator::OperatorNew(@1, "!");
                        $$ = new LogicalExpr(op, $2);
                    }
                  | T_New '(' T_Identifier ')' {
                      Identifier::Ptr id = Identifier::IdentifierNew(@3, $3);
                      NamedType::Ptr type = NamedType::NamedTypeNew(id);
                      $$ = new NewExpr(Join(@1, @4), type);
                    }
                  | T_NewArray '(' Expr ',' Type ')' {
                      $$ = new NewArrayExpr(Join(@1, @6), $3, $5);
                    }
                  | T_ReadInteger '(' ')' { $$ = new ReadIntegerExpr(@1); }
                  | T_ReadLine '(' ')'    { $$ = new ReadLineExpr(@1);    }
                  | T_This                { $$ = new ThisExpr(@1);        }
                  ;

LValue            : T_Identifier {
                      Identifier::Ptr id = Identifier::IdentifierNew(@1, $1);
                      $$ = new VarAccessExpr(id);
                    }
                  | Expr '.' T_Identifier {
                      Identifier::Ptr field = Identifier::IdentifierNew(@3, $3);
                      $$ = new FieldAccessExpr($1, field);
                    }
                  | Expr '[' Expr ']' {
                      $$ = new ArrayAccessExpr(Join(@1, @4), $1, $3);
                    }
                  ;

Call              : T_Identifier '(' Actuals ')' {
                      Identifier::Ptr field = Identifier::IdentifierNew(@1, $1);
                      $$ = new CallExpr(Join(@1, @4), NULL, field, $3);
                    }
                  | Expr '.' T_Identifier '(' Actuals ')' {
                        Identifier::Ptr field;
                        field = Identifier::IdentifierNew(@3, $3);
                        $$ = new CallExpr(Join(@1, @6), $1, field, $5);
                    }
                  ;

Actuals           : ExprList    { $$ = $1; }
                  | /* empty */ { $$ = new Deque<Expr::Ptr>(); }
                  ;

Constant          : T_IntConstant { $$ = new IntConstExpr(@1, $1); }
                  | T_DoubleConstant { $$ = new DblConstExpr(@1, $1); }
                  | T_BoolConstant { $$ = new BoolConstExpr(@1, $1);   }
                  | T_StringConstant { $$ = new StrConstExpr(@1, $1); }
                  | T_Null { $$ = new NullConstExpr(@1); }
                  ;

%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
