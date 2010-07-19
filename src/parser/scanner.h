/* File: scanner.h
 * ---------------
 * You should not need to modify this file. It declares a few constants,
 * types, variables,and functions that are used and/or exported by
 * the lex-generated scanner.
 */

#ifndef _H_scanner
#define _H_scanner

#include <stdio.h>

const int kMaxIdentifierLength = 31;

extern char *yytext;      // Text of lexeme just scanned


int yylex();              // Defined in the generated lex.yy.c file

void InitScanner();                 // Defined in scanner.l user subroutines
const char *GetLineNumbered(int n); // ditto
 
#endif
