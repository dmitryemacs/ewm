CC = clang
CFLAGS = -O2 -Wall -Wextra -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lX11

SRCS = main.c keybindings.c
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
