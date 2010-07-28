/* File: errors.cc
 * ---------------
 * Implementation for error-reporting class.
 */

#include "errors.h"
#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>

#include "parser/scanner.h" // for GetLineNumbered

/* ast includes */
#include "ast.h"

int ReportError::numErrors = 0;

void
ReportError::UnderlineErrorInLine(const char *line, yyltype *pos) {
  if (!line)
    return;

  cerr << line << endl;
  for (int i = 1; i <= pos->last_column; i++)
    cerr << (i >= pos->first_column ? '^' : ' ');
  cerr << endl;
}

void
ReportError::OutputError(yyltype *loc, string msg) {
  numErrors++;

  /* make sure any buffered text has been output */
  fflush(stdout);
  if (loc) {
    cerr << endl << "*** Error line " << loc->first_line << "." << endl;
    UnderlineErrorInLine(GetLineNumbered(loc->first_line), loc);
  } else {
    cerr << endl << "*** Error." << endl;
  }
  cerr << "*** " << msg << endl << endl;
}

void
ReportError::Formatted(yyltype *loc, const char *format, ...) {
  va_list args;
  char errbuf[2048];

  va_start(args, format);
  vsprintf(errbuf,format, args);
  va_end(args);
  OutputError(loc, errbuf);
}

void
ReportError::UntermComment() {
  OutputError(NULL, "Input ends with unterminated comment");
}


void
ReportError::LongIdentifier(yyltype *loc, const char *ident) {
  ostringstream s;
  s << "Identifier too long: \"" << ident << "\"";
  OutputError(loc, s.str());
}

void
ReportError::UntermString(yyltype *loc, const char *str) {
  ostringstream s;
  s << "Unterminated string constant: " << str;
  OutputError(loc, s.str());
}

void
ReportError::UnrecogChar(yyltype *loc, char ch) {
  ostringstream s;
  s << "Unrecognized char: '" << ch << "'";
  OutputError(loc, s.str());
}

void
ReportError::DeclConflict(Decl *decl, Decl *prevDecl) {
  ostringstream s;
  s << "Declaration of '" << decl;
  s << "' here conflicts with declaration on line ";
  s << prevDecl->lexLoc()->first_line;
  OutputError(decl->lexLoc(), s.str());
}

void
ReportError::OverrideMismatch(Decl *fnDecl) {
  ostringstream s;
  s << "Method '" << fnDecl << "' must match inherited type signature";
  OutputError(fnDecl->lexLoc(), s.str());
}

void
ReportError::InterfaceNotImplemented(Decl *cd, Type *interfaceType) {
  ostringstream s;
  s << "Class '" << cd;
  s << "' does not implement entire interface '" << interfaceType << "'";
  OutputError(interfaceType->lexLoc(), s.str());
}

void
ReportError::IdentifierNotDeclared(Identifier *ident, reasonT whyNeeded) {
  ostringstream s;
  static const char *names[] = {
    "type", "class", "interface", "variable", "function"
  };

  assert(whyNeeded >= 0 && whyNeeded <= sizeof(names)/sizeof(names[0]));
  s << "No declaration found for "<< names[whyNeeded] << " '" << ident << "'";
  OutputError(ident->lexLoc(), s.str());
}

void
ReportError::IncompatibleOperands(Operator *op, Type *lhs, Type *rhs) {
  ostringstream s;
  s << "Incompatible operands: " << lhs << " " << op << " " << rhs;
  OutputError(op->lexLoc(), s.str());
}

void
ReportError::IncompatibleOperand(Operator *op, Type *rhs) {
  ostringstream s;
  s << "Incompatible operand: " << op << " " << rhs;
  OutputError(op->lexLoc(), s.str());
}

void
ReportError::ThisOutsideClassScope(ThisExpr *th) {
  OutputError(th->lexLoc(), "'this' is only valid within class scope");
}

void
ReportError::BracketsOnNonArray(Expr *baseExpr) {
  OutputError(baseExpr->lexLoc(), "[] can only be applied to arrays");
}

void
ReportError::SubscriptNotInteger(Expr *subscriptExpr) {
  OutputError(subscriptExpr->lexLoc(), "Array subscript must be an integer");
}

void
ReportError::NewArraySizeNotInteger(Expr *sizeExpr) {
  OutputError(sizeExpr->lexLoc(), "Size for NewArray must be an integer");
}

void
ReportError::NumArgsMismatch(Identifier *fnIdent,
                             int numExpected, int numGiven) {
  ostringstream s;
  s << "Function '"<< fnIdent << "' expects ";
  s << numExpected << " argument" << (numExpected == 1 ? "" : "s");
  s << " but " << numGiven << " given";
  OutputError(fnIdent->lexLoc(), s.str());
}

void
ReportError::ArgMismatch(Expr *arg, int argIndex, Type *given, Type *expected) {
  ostringstream s;
  s << "Incompatible argument " << argIndex << ": ";
  s << given << " given, " << expected << " expected";
  OutputError(arg->lexLoc(), s.str());
}

void
ReportError::ReturnMismatch(ReturnStmt *rStmt, Type *given, Type *expected) {
  ostringstream s;
  s << "Incompatible return: " << given << " given, ";
  s << expected << " expected";
  OutputError(rStmt->lexLoc(), s.str());
}

void
ReportError::FieldNotFoundInBase(Identifier *field, Type *base) {
  ostringstream s;
  s << base << " has no such field '" << field <<"'";
  OutputError(field->lexLoc(), s.str());
}

void
ReportError::InaccessibleField(Identifier *field, Type *base) {
  ostringstream s;
  s  << base << " field '" << field << "' only accessible within class scope";
  OutputError(field->lexLoc(), s.str());
}

void
ReportError::PrintArgMismatch(Expr *arg, int argIndex, Type *given) {
  ostringstream s;
  s << "Incompatible argument " << argIndex << ": " << given;
  s << " given, int/bool/string expected";
  OutputError(arg->lexLoc(), s.str());
}

void
ReportError::TestNotBoolean(Expr *expr) {
  OutputError(expr->lexLoc(), "Test expression must have boolean type");
}

void
ReportError::BreakOutsideLoop(BreakStmt *bStmt) {
  OutputError(bStmt->lexLoc(), "break is only allowed inside a loop");
}

void
ReportError::NoMainFound() {
  OutputError(NULL, "Linker: function 'main' not defined");
}

/* Function: yyerror()
 * -------------------
 * Standard error-reporting function expected by yacc. Our version merely
 * just calls into the error reporter above, passing the location of
 * the last token read. If you want to suppress the ordinary "parse error"
 * message from yacc, you can implement yyerror to do nothing and
 * then call ReportError::Formatted yourself with a more descriptive
 * message.
 */

void yyerror(const char *msg, yyltype *loc) {
    yyltype *location = (loc) ? loc : &yylloc;
    ReportError::Formatted(location, "%s", msg);
}
