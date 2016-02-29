#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
CC := gcc
RM := rm -rf
MD := mkdir

#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------
all: ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o ./Build/parserTable.o ./Build/stack.o ./Build/lexer.o ./Build/parser.o
	@echo 'compiling and linking final code'
	@$(CC) -o run run.c ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o ./Build/parserTable.o ./Build/stack.o ./Build/lexer.o ./Build/parser.o
	@echo 'Built target run'

./Build/parser.o: ./Build/stack.o ./Build/parserTable.o parser.h parser.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parser.c -o $@
	@echo ' Done'

./Build/stack.o: ./Build/parserUtils.o stack.h stack.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c stack.c -o $@
	@echo ' Done'

./Build/parserTable.o: ./Build/parserSets.o parserTable.h parserTable.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserTable.c -o $@
	@echo ' Done'

./Build/parserSets.o: ./Build/set.o parserSets.h parserSets.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserSets.c -o $@
	@echo ' Done'

./Build/set.o: ./Build/parserUtils.o set.h set.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c set.c -o $@
	@echo ' Done'

./Build/parserUtils.o: ./Build/lexer.o parserDef.h parserUtils.h parserUtils.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserUtils.c -o $@
	@echo ' Done'

./Build/lexer.o: lexerDef.h lexer.h lexer.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c lexer.c -o $@
	@echo ' Done'

clean:
	$(RM) run
	$(RM) ./Build
