CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm
TARGET  = artemis
SRCS    = main.c simulador.c validaciones.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
  $(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c simulador.h validaciones.h
  $(CC) $(CFLAGS) -c $< -o $@

clean:
  rm -f $(OBJS) $(TARGET)

.PHONY: all clean
