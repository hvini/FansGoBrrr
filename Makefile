# === Compiler settings ===
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2
LDFLAGS =

# === Directories ===
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = build
TEST_BUILD_DIR = $(OBJ_DIR)/tests

# === Source files ===
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
# Shared sources for tests (exclude main.c)
SHARED_SRC := $(filter-out $(SRC_DIR)/main.c, $(SRC_FILES))

# === Test files ===
TEST_FILES := $(wildcard $(TEST_DIR)/test_*.c)
TEST_NAMES := $(notdir $(basename $(TEST_FILES))) # e.g., test_matrix
TEST_BINS := $(addprefix $(TEST_BUILD_DIR)/, $(TEST_NAMES))

# === Targets ===
TARGET = $(OBJ_DIR)/main

# === Build main application ===
all: $(TARGET)

$(TARGET): $(OBJ_DIR)/main.o $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SHARED_SRC))
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# === Build shared objects for tests ===
TEST_SHARED_OBJS := $(patsubst $(SRC_DIR)/%.c,$(TEST_BUILD_DIR)/%.o,$(SHARED_SRC))

$(TEST_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# === Compile test objects ===
$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# === Link test binaries ===
$(TEST_BUILD_DIR)/%: $(TEST_BUILD_DIR)/%.o $(TEST_SHARED_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# === Run tests ===
test: $(TEST_BINS)
	@echo "Running tests..."
	@for test_bin in $(TEST_BINS); do \
		echo "==> $$test_bin"; \
		./$$test_bin || exit 1; \
	done
	@echo "All tests passed."

# === Clean everything ===
clean:
	rm -rf $(OBJ_DIR)

# === Clean tests only ===
clean-test:
	rm -rf $(TEST_BUILD_DIR)

.PHONY: all clean clean-test test

