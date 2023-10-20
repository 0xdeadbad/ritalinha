include ../common.mk

_OBJ_DIR := $(TOP_DIR)/$(OBJ_DIR)
OBJ := $(patsubst %,$(_OBJ_DIR)/%,$(${MODULE}_OBJ))

_INC_DIR := $(TOP_DIR)/$(INC_DIR)
DEPS := $(patsubst %,$(_INC_DIR)/%,$(${MODULE}_DEPS))

$(_OBJ_DIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJ)
