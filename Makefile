# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2
LDFLAGS = 
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = build

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Shared source files (exclude main.c from test builds)
SHARED_SRC_FILES := $(filter-out $(SRC_DIR)/main.c, $(SRC_FILES))
SHARED_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SHARED_SRC_FILES))

# Test files
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_FILES))

# Targets
TARGET = $(OBJ_DIR)/main
TEST_TARGET = $(OBJ_DIR)/test_matrix

all: $(TARGET)

# Main binary
$(TARGET): $(OBJ_DIR)/main.o $(SHARED_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compile .c from src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile .c from tests/
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Test binary (only link test object + shared objects, exclude main.o)
test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJ_DIR)/test_matrix.o $(SHARED_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*

.PHONY: all clean test

