CC = gcc
CFLAGS = -Wall -std=gnu99 -pthread
TARGET = monitor_server monitor_client

all: $(TARGET)

monitor_server: monitor_server.c ../net.c
	$(CC) $(CFLAGS) $^ -o $@

monitor_client: monitor_client.c ../net.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) *.exe
