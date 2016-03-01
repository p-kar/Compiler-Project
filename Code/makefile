#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
CC := gcc
RM := rm -rf
MD := mkdir

#---------------------------------------------------------------------
# utilities
#---------------------------------------------------------------------
NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m
NOTIFY_COLOR=\x1b[34;01m

#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------
all: ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o ./Build/parserTable.o ./Build/stack.o ./Build/lexer.o ./Build/parser.o
	@echo "$(NOTIFY_COLOR)compiling and linking final code$(NO_COLOR)"
	@$(CC) -o run run.c ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o ./Build/parserTable.o ./Build/stack.o ./Build/lexer.o ./Build/parser.o
	@echo "$(WARN_COLOR)Built target run$(NO_COLOR)"

./Build/parser.o: ./Build/stack.o ./Build/parserTable.o parser.h parser.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parser.c -o $@
	@echo "$(OK_COLOR) Done$(NO_COLOR)"

./Build/stack.o: ./Build/parserUtils.o stack.h stack.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c stack.c -o $@
	@echo "$(OK_COLOR) Done$(NO_COLOR)"

./Build/parserTable.o: ./Build/parserSets.o parserTable.h parserTable.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserTable.c -o $@
	@echo "$(OK_COLOR) Done$(NO_COLOR)"

./Build/parserSets.o: ./Build/set.o parserSets.h parserSets.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserSets.c -o $@
	@echo "$(OK_COLOR) Done$(NO_COLOR)"

./Build/set.o: ./Build/parserUtils.o set.h set.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c set.c -o $@
	@echo "$(OK_COLOR) Done$(NO_COLOR)"

./Build/parserUtils.o: ./Build/lexer.o parserDef.h parserUtils.h parserUtils.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserUtils.c -o $@
	@echo "$(OK_COLOR) Done$(NO_COLOR)"

./Build/lexer.o: lexerDef.h lexer.h lexer.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c lexer.c -o $@
	@echo "$(OK_COLOR) Done$(NO_COLOR)"

clean:
	$(RM) run
	$(RM) ./Build
