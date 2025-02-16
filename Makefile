CC := gcc
CFLAGS := -Wall -g
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.c)
TARGET := tigran

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean

clean:
	rm -f $(TARGET)