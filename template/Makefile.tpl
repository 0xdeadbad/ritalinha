include common.mk

CFLAGS += -I$(INC_DIR) -I$(3RDPARTY_DIR)

_OBJ := main.o
OBJ := $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
OBJ += $(patsubst %,$(OBJ_DIR)/%,$(cJSON_OBJ))
${OBJ_PATSUBST}

$(OBJ_DIR)/%.o: $(cJSON_DIR)/%.c $(_cJSON_DEPS)
	$(MAKE) -C $(3RDPARTY_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(3RDPARTY_DIR) -o $@ -c $<
${MODULES_TARGETS}

all: $(OBJ_DIR) $(BIN)

.PHONY: $(OBJ_DIR) $(BIN) clean

$(OBJ_DIR): ; @mkdir -p $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)
	rmdir $(OBJ_DIR)