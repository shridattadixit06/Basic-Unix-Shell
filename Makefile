CC = gcc

CFLAGS = -Iinclude

SRC = shell.c \
      src/builtins.c \
      src/config.c \
      src/executor.c \
      src/jobs.c \
      src/parser.c \
      src/redirect.c

TARGET = myshell

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)