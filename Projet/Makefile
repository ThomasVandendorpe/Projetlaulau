EXEC=appli

SRC=src
HEADERS=Include

CC=gcc
CFLAGS=-Wall -Werror -I./$(HEADERS)
LDFLAGS=

#############################################################

all: $(EXEC)

$(EXEC): $(patsubst $(SRC)/%.c,%.o,$(shell ls $(SRC)/*.c))
	$(CC) -o $@ $^ $(LDFLAGS) 

%.o:$(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o



