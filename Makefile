CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Isrc

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/fetch.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = myfetch

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

install: $(TARGET)
	install -m 755 $(TARGET) /usr/bin/$(TARGET)
	mkdir -p /etc/xdg/myfetch && cp config/config /etc/xdg/myfetch

uninstall:
	rm -f /usr/bin/$(TARGET)
	rm -rf /etc/xdg/myfetch

.PHONY: all clean run install uninstall
