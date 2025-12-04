CC = gcc
CFLAGS = -Wall -pthread
TARGET = dining

all: $(TARGET)

$(TARGET): dining_philosophers.c
$(CC) $(CFLAGS) dining_philosophers.c -o $(TARGET)

run:
	$(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
