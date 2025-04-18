CC = gcc

CFLAGS = -Wall -Wextra -std=c11 $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

BUILD_DIR = build
SRC_DIR = .
TARGET = main

SRC = 4Gewinnt.c minimax_logik.c loop_logik.c minimax.c selbst_spielen.c suchen_bot.c rand_bot.c spiellogik.c
HEADERS = 4Gewinnt.h

OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
