EXEC=appli AllTests
appli:
AllTests:

COUVERTURE=y

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
#############################################################

all: $(EXEC)

%.o:$(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o $(patsubst $(SRC)/%.c,%.o,$(shell grep -L "int main" $(SRC)/*.c))
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm *.o *.gcda *.gcno $(EXEC)



