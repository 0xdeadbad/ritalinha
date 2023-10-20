include common.mk

cJSON_DIR := cJSON

_OBJ_DIR := $(TOP_DIR)/$(OBJ_DIR)
OBJ := $(patsubst %,$(_OBJ_DIR)/%,$(cJSON_OBJ))

_INC_DIR := $(cJSON_DIR)
DEPS := $(patsubst %,$(_INC_DIR)/%,$(cJSON_DEPS))

CFLAGS += -IcJSON

$(_OBJ_DIR)/%.o: $(cJSON_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJ)