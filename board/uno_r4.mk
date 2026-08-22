CPU := cortex-m4
LINKER_SCRIPT := ld/R7FA4M1AB.ld

SVD := svd/R7FA4M1AB.svd

DEBUG_ADAPTER ?= jlink
JLINK_DEVICE := R7FA4M1AB3CFM

INC_DIRS += \
  src/board/uno_r4

DEFINES += \
