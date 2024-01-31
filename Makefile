CC = clang

CFLAGS  = --std=c99 -Wall -Wextra -DGL_DEBUG
LDFLAGS = -lgdi32 -lopengl32

SRC  = $(wildcard src/*.c)
OBJ  = $(SRC:.c=.o)
OUT  = tinybox

build: $(OBJ)
	$(CC) -o $(OUT) $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)