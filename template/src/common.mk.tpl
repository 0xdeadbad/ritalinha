TOP_DIR := ../..
include config.mk
include $(TOP_DIR)/config.mk
CFLAGS += -I$(TOP_DIR)/include -I$(TOP_DIR)/3rdparty