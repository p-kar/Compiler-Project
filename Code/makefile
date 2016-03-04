# @Author:    Pratyush Kar (2013A7PS029P),
#             Ayush Kataria (2013A7PS028P)
# @Email:     f2013029@pilani.bits-pilani.ac.in,
#             f2013028@pilani.bits-pilani.ac.in
# @Gp Number: 52
# @File Name: makefile
# @Date:      2016-02-18 12:47:17

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
	@tput bold
	@echo $1
	@tput sgr0
endef

define errorecho
	@tput setaf 1
	@tput bold
	@echo $1
	@tput sgr0
endef

define warnecho
	@tput setaf 5
	@tput bold
	@echo $1
	@tput sgr0
endef

define notifyecho
	@tput setaf 6
	@tput bold
	@echo $1
	@tput sgr0
endef

#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------
all: ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o ./Build/stack.o ./Build/lexer.o ./Build/parser.o
	$(call notifyecho, "compiling and linking final code")
	@$(CC) -o run run.c ./Build/*.o
	$(call warnecho, "Built target run")
	@$(CC) -o driver driver.c ./Build/*.o
	$(call warnecho, "Built target driver")

./Build/parser.o: ./Build/stack.o ./Build/parserSets.o parser.h parser.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parser.c -o $@
	$(call okecho, " Done")

./Build/stack.o: ./Build/parserUtils.o stack.h stack.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c stack.c -o $@
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
	$(RM) driver
	$(RM) ./Build
