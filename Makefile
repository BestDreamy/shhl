TOP_NAME = switch

VERILATOR_FLAGS = -cc --exe --build --trace-fst --top-module $(TOP_NAME)

CSRCS = $(shell find $(abspath ./) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOP_NAME)

default: run

$(BIN): $(CSRCS) $(VSRCS) | $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	verilator $(VERILATOR_FLAGS) $^ \
	--Mdir $(OBJ_DIR) -o $(abspath $(BIN))

run: $(BIN)
	@$^

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR) wave.fst

.PHONY: default all clean run