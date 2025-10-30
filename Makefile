CC = clang
CFLAGS = -O2 -Wall -Wextra -I/usr/local/include -I./include
LDFLAGS = -L/usr/local/lib -lX11

SRCS = src/keybindings.c src/workspaces.c src/utils.c main.c
OBJS = $(SRCS:.c=.o)
TARGET = ewm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean run
