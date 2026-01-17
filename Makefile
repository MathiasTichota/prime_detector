CC = gcc
# -O3: Maximum optimization
# -march=native: Optimize for the host CPU (very Arch-like)
# -Wall -Wextra: Enable all warnings for safety
CFLAGS = -Wall -Wextra -O3 -march=native

TARGET = main

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET) *.o
