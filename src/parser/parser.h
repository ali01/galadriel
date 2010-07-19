/* File: parser.h
 * --------------
 * This file provides constants and type definitions that will
 * be used and/or exported by the yacc-generated parser. */

#ifndef PARSER_H_DOKDNAG1
#define PARSER_H_DOKDNAG1

/* include components needed for the yylval union */
#include "scanner.h" /* for kMaxIdentifierLength */

/* ast includes */
#include "ast.h"


/* We want to get the exported defines for the token codes and
   typedef for YYSTYPE and exported global variable yylval.  These
   definitions are generated and written to the y.tab.h header file. But
   because that header does not have any protection against being
   re-included and those definitions are also present in the y.tab.c,
   we can get into trouble if we don't take precaution to not include if
   we are compiling y.tab.c, which we use the YYBISON symbol for. */

#ifndef YYBISON
#include "y.tab.h"
#endif

int yyparse(); /* Defined in the generated y.tab.c file */
void InitParser(); /* Defined in parser.y */

#endif
