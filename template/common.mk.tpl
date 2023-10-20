include config.mk

3RDPARTY_DIR := $(3RD_DIR)

cJSON_DIR := $(3RDPARTY_DIR)/cJSON
${MODULES_DIRS}

include $(3RDPARTY_DIR)/config.mk
${MODULES_INCS}

_cJSON_DEPS := $(patsubst %,$(cJSON_DIR)/%,$(cJSON_DEPS))
${MODULES_DEPS}

BIN := ritalinha
