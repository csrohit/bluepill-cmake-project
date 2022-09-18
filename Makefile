.PHONY: all build cmake clean format

BUILD_DIR := build
BUILD_TYPE ?= Debug

all: build

${BUILD_DIR}/Makefile:
	cmake \
		-B${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_TOOLCHAIN_FILE=gcc-arm-none-eabi.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DDUMP_ASM=ON

cmake: ${BUILD_DIR}/Makefile

build: cmake
	$(MAKE) -C ${BUILD_DIR} --no-print-directory

flash:
	openocd -d2 -f interface/stlink.cfg -c "transport select hla_swd" -f target/stm32f1x.cfg -c "program {build/blink.elf}  verify reset; shutdown;"


SRCS := $(shell find . -name '*.[ch]' -or -name '*.[ch]pp')


clean:
	rm -rf $(BUILD_DIR)
