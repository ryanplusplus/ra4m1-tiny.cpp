include tools/setup.mk

TARGET := target
BOARD ?= uno_r4
BUILD_DIR := ./build/$(BOARD)

include board/$(BOARD).mk
include tools/defaults.mk

CXXFLAGS += \
  -std=c++20 \

INC_DIRS += \

SYS_INC_DIRS += \

SRC_FILES += \

SRC_DIRS += \
  src \

include lib_fsp.mk
include lib/tiny.cpp/lib_tiny_cpp.mk
include lib/tiny-rtt/lib_tiny-rtt.mk
include lib_hardware.mk

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex
	@$(SIZE) $<

.PHONY: watch
watch:
	@rerun "$(MAKE) --no-print-directory -f $(firstword $(MAKEFILE_LIST))"

include tools/tools.mk
include docs.mk
