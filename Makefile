TOP_NAME = switch

VERILATOR_FLAGS = -cc --exe --build --trace-fst --top-module $(TOP_NAME)

CSRCS = $(shell find $(abspath ./) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOP_NAME)

CXXFLAGS = -MMD -MP

# Just for testing
TEST_DIR = $(abspath ./benchmark)
test ?= allReduce
TEST-SRC = $(TEST_DIR)/$(test).txt

default: run

$(BIN): $(CSRCS) $(VSRCS) | $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	verilator $(VERILATOR_FLAGS) $(CXXFLAGS) $^ \
	--Mdir $(OBJ_DIR) -o $(abspath $(BIN))

run: $(BIN) $(TEST-SRC)
	@$(BIN) $(TEST-SRC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR) wave.fst

commit ?= update
git:
	git add .
	git commit -m "$(commit)"
	git push

.PHONY: default all clean run