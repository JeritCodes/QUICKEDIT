# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -I/usr/include/SDL2 -I/usr/include/SDL2_image
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image

# Source files
SRCS = QuickEdit.c bitmap.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = QuickEdit

# Default target
all: $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Clean up build files
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
