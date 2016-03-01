#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
CC := gcc
RM := rm -rf
MD := mkdir

#---------------------------------------------------------------------
# utilities
#---------------------------------------------------------------------
define okecho
	@tput setaf 2
	@echo $1
	@tput sgr0
endef

define errorecho
	@tput setaf 1
	@echo $1
	@tput sgr0
endef

define warnecho
	@tput setaf 3
	@echo $1
	@tput sgr0
endef

define notifyecho
	@tput setaf 6
	@echo $1
	@tput sgr0
endef

#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------
all: ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o ./Build/parserTable.o ./Build/stack.o ./Build/lexer.o ./Build/parser.o
	$(call notifyecho, "compiling and linking final code")
	@$(CC) -o run run.c ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o ./Build/parserTable.o ./Build/stack.o ./Build/lexer.o ./Build/parser.o
	$(call warnecho, "Built target run")

./Build/parser.o: ./Build/stack.o ./Build/parserTable.o parser.h parser.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parser.c -o $@
	$(call okecho, " Done")

./Build/stack.o: ./Build/parserUtils.o stack.h stack.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c stack.c -o $@
	$(call okecho, " Done")

./Build/parserTable.o: ./Build/parserSets.o parserTable.h parserTable.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserTable.c -o $@
	$(call okecho, " Done")

./Build/parserSets.o: ./Build/set.o parserSets.h parserSets.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserSets.c -o $@
	$(call okecho, " Done")

./Build/set.o: ./Build/parserUtils.o set.h set.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c set.c -o $@
	$(call okecho, " Done")

./Build/parserUtils.o: ./Build/lexer.o parserDef.h parserUtils.h parserUtils.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserUtils.c -o $@
	$(call okecho, " Done")

./Build/lexer.o: lexerDef.h lexer.h lexer.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c lexer.c -o $@
	$(call okecho, " Done")

clean:
	$(RM) run
	$(RM) ./Build
