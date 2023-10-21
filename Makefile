CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =

TARGET = hugepage_alloc

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGET)

