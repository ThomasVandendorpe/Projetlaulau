EXEC=appli

SRC=src
HEADERS=Include

CC=gcc
CFLAGS=-Wall -Werror -I./$(HEADERS) -fprofile-arcs -ftest-coverage -g
LDFLAGS= -fprofile-arcs -ftest-coverage

#BCFILES=...c ...c
#############################################################

all: $(EXEC)

AllTests: $(patsubst $(SRC)/%.c,%.o,$(shell ls $(SRC)/*.c))
	$(CC) -o $@ $^ $(LDFLAGS) -D_MAIN_
#llvm-link ?
$(EXEC): $(patsubst $(SRC)/%.c,%.o,$(shell ls $(SRC)/*.c))
	$(CC) -o $@ $^ $(LDFLAGS)
	
%.o:$(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
#-emit-llvm

#complete.bc : $(BCFILES)
	#llvm-link $+ -o $@

#%.bc : %.c
	#clang $(CFLAGS) -c -emit-llvm $<

clean:
	rm *.o *.gcda *.gcno



