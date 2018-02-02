EXEC=appli

SRC=src
HEADERS=Include
OBJETS=obj

CC=gcc
CFLAGS=-Wall -Werror -I./$(HEADERS)
LDFLAGS=

#############################################################

all: $(EXEC)

$(EXEC): $(patsubst $(SRC)%.c,$(OBJETS)%.o,$(shell ls $(SRC)/*.c))
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJETS)/%.o:$(SRC)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	rm $(EXEC) $(OBJETS)/*.o




