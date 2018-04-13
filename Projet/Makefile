EXEC=appli


#Juste pour utiliser l'autocomplétion via tabulation:
appli:
AllTests:
#####
#####
#Mettrer y comme valeur pour activer:

COUVERTURE=y
PROFILING=y
FUZZING=n

#note: FUZZING n'est pas compatible avec COUVERTURE et PROFILING.
#####
SRC=src
HEADERS=Include

CC=gcc
CFLAGS= -I./$(HEADERS) -g
LDFLAGS=

#############################################################
ifeq ($(COUVERTURE),y)
	CFLAGS+= -fprofile-arcs -ftest-coverage 
	LDFLAGS+= -fprofile-arcs -ftest-coverage
endif
ifeq ($(PROFILING),y)
	CFLAGS+= -pg
	LDFLAGS+= -pg
endif
ifeq ($(FUZZING),y)
	CC=afl-gcc
endif
#############################################################

all: $(EXEC) AllTests

#compilation
%.o:$(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#édition de liens
%: %.o $(patsubst $(SRC)/%.c,%.o,$(shell grep -L "int main" $(SRC)/*.c))
	$(CC) -o $@ $^ $(LDFLAGS)

#exécution du profiling (arguments de l'exécutable passé en paramètre)
profiling: appli
	./appli $(args) < exemples/input/input100.txt > /dev/null
	gprof ./appli > profiling.txt

fuzzing: appli
	AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=ON AFL_SKIP_CPUFREQ=ON afl-fuzz -i afl_in/ -o afl_out/ ./appli config1.xml

tests: AllTests
	./AllTests config1.xml

documentation: Doxyfile $(shell ls $(SRC)/*.c)
	doxygen Doxyfile
	firefox documentation/html/index.html



clean:
	rm *.o *.gcda *.gcno $(EXEC) AllTests



