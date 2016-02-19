#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
CC := gcc
RM := rm -rf
MD := mkdir

#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------
all: ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o
	@echo 'compiling and linking final code'
	@$(CC) -o run run.c ./Build/parserUtils.o ./Build/set.o ./Build/parserSets.o
	@echo 'Built target run'

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

./Build/parserUtils.o: parserDef.h parserUtils.h parserUtils.c
	@echo -n Building $@...
	@if !(test -d ./Build); then $(MD) ./Build; fi
	@$(CC) -c parserUtils.c -o $@
	@echo ' Done'

clean:
	rm -rf run
	rm -rf ./Build
