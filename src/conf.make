PROJECT       := dcc
SUBDIRS       := ast parser semantic_analyser simone

LIBS          := -lc -lm -ll
EXTERNAL_OBJS := parser/y.tab.o parser/lex.yy.o
CXXFLAGS      += -Wno-unused -Wno-sign-compare
CPPFLAGS      += -I.

LEX           := flex
YACC          := bison

LEXFLAGS      := -d
YACCFLAGS     := -dvty

TRASH += parser/y.tab.h parser/y.tab.c parser/y.output parser/lex.yy.c log.diff
TRASH += samples/*.test

parser/lex.yy.c: parser/scanner.l parser/parser.y parser/y.tab.h
	cd parser; $(LEX) $(LEXFLAGS) scanner.l

parser/lex.yy.o: parser/lex.yy.c
	@$(CXX) $(CPPFLAGS) -MM -MP -MF $(basename $<).d -MT $(basename $<).o $<
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) parser/lex.yy.c -o parser/lex.yy.o

parser/y.tab.o: parser/y.tab.c
	@$(CXX) $(CPPFLAGS) -MM -MP -MF $(basename $<).d -MT $(basename $<).o $<
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) parser/y.tab.c -o parser/y.tab.o

parser/y.tab.h parser/y.tab.c: parser/parser.y
	cd parser; $(YACC) $(YACCFLAGS) parser.y

.PHONY: strip

strip: $(PROJECT)
	strip $(PROJECT)
	rm -rf $(TRASH)
