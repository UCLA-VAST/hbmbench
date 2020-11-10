
.PHONY: help

help::
	$(ECHO) "Makefile Usage:"
	$(ECHO) "  make all TARGET=<sw_emu/hw_emu/hw> DEVICE=<FPGA platform> HOST_ARCH=<aarch32/aarch64/x86> SYSROOT=<sysroot_path>"
	$(ECHO) "      Command to generate the design for specified Target and Shell."
	$(ECHO) "      By default, HOST_ARCH=x86. HOST_ARCH and SYSROOT is required for SoC shells"
	$(ECHO) ""
	$(ECHO) "  make clean "
	$(ECHO) "      Command to remove the generated non-hardware files."
	$(ECHO) ""
	$(ECHO) "  make cleanall"
	$(ECHO) "      Command to remove all the generated files."
	$(ECHO) ""
	$(ECHO) "  make sd_card TARGET=<sw_emu/hw_emu/hw> DEVICE=<FPGA platform> HOST_ARCH=<aarch32/aarch64/x86> SYSROOT=<sysroot_path>"
	$(ECHO) "      Command to prepare sd_card files."
	$(ECHO) "      By default, HOST_ARCH=x86. HOST_ARCH and SYSROOT is required for SoC shells"
	$(ECHO) ""
	$(ECHO) "  make check TARGET=<sw_emu/hw_emu/hw> DEVICE=<FPGA platform> HOST_ARCH=<aarch32/aarch64/x86> SYSROOT=<sysroot_path>"
	$(ECHO) "      Command to run application in emulation."
	$(ECHO) "      By default, HOST_ARCH=x86. HOST_ARCH and SYSROOT is required for SoC shells"
	$(ECHO) ""
	$(ECHO) "  make build TARGET=<sw_emu/hw_emu/hw> DEVICE=<FPGA platform> HOST_ARCH=<aarch32/aarch64/x86> SYSROOT=<sysroot_path>"
	$(ECHO) "      Command to build xclbin application."
	$(ECHO) "      By default, HOST_ARCH=x86. HOST_ARCH and SYSROOT is required for SoC shells"
	$(ECHO) ""

# Points to top directory of Git repository
COMMON_REPO = ../
PWD = $(shell readlink -f .)
ABS_COMMON_REPO = $(shell readlink -f $(COMMON_REPO))

TARGET := hw
HOST_ARCH := x86
SYSROOT := 
#DEVICE = xilinx_u50_gen3x16_xdma_201920_3
DEVICE = xilinx_u280_xdma_201920_3

include ./utils.mk

XSA := $(call device2xsa, $(DEVICE))
TEMP_DIR := ./_x.$(TARGET).$(XSA)
BUILD_DIR := ./build_dir.$(TARGET).$(XSA)

VPP := v++
SDCARD := sd_card

#Include Libraries
include $(ABS_COMMON_REPO)/common/includes/opencl/opencl.mk
include $(ABS_COMMON_REPO)/common/includes/xcl2/xcl2.mk
CXXFLAGS += $(xcl2_CXXFLAGS)
LDFLAGS += $(xcl2_LDFLAGS)
HOST_SRCS += $(xcl2_SRCS)
CXXFLAGS += $(opencl_CXXFLAGS) -Wall -O0 -g -std=c++11
LDFLAGS += $(opencl_LDFLAGS)

HOST_SRCS += src/host.cpp

# Host compiler global settings
CXXFLAGS += -fmessage-length=0
LDFLAGS += -lrt -lstdc++ 

ifneq ($(HOST_ARCH), x86)
	LDFLAGS += --sysroot=$(SYSROOT)
endif

# Kernel compiler global settings
CLFLAGS += -t $(TARGET) --platform $(DEVICE) --save-temps 
ifneq ($(TARGET), hw)
	CLFLAGS += -g
endif

CLFLAGS += --sp vadd_1.in0_0_0:HBM[0]
CLFLAGS += --sp vadd_1.in0_0_1:HBM[0]
CLFLAGS += --sp vadd_1.in0_0_2:HBM[0]
CLFLAGS += --sp vadd_1.in0_0_3:HBM[0]
CLFLAGS += --sp vadd_1.in0_0_4:HBM[0]
CLFLAGS += --sp vadd_1.in0_0_5:HBM[0]
CLFLAGS += --sp vadd_1.in0_0_6:HBM[0]
CLFLAGS += --sp vadd_1.in0_0_7:HBM[0]
CLFLAGS += --sp vadd_1.in0_1_0:HBM[1]
CLFLAGS += --sp vadd_1.in0_1_1:HBM[1]
CLFLAGS += --sp vadd_1.in0_1_2:HBM[1]
CLFLAGS += --sp vadd_1.in0_1_3:HBM[1]
CLFLAGS += --sp vadd_1.in0_1_4:HBM[1]
CLFLAGS += --sp vadd_1.in0_1_5:HBM[1]
CLFLAGS += --sp vadd_1.in0_1_6:HBM[1]
CLFLAGS += --sp vadd_1.in0_1_7:HBM[1]
CLFLAGS += --sp vadd_1.in0_2_0:HBM[2]
CLFLAGS += --sp vadd_1.in0_2_1:HBM[2]
CLFLAGS += --sp vadd_1.in0_2_2:HBM[2]
CLFLAGS += --sp vadd_1.in0_2_3:HBM[2]
CLFLAGS += --sp vadd_1.in0_2_4:HBM[2]
CLFLAGS += --sp vadd_1.in0_2_5:HBM[2]
CLFLAGS += --sp vadd_1.in0_2_6:HBM[2]
CLFLAGS += --sp vadd_1.in0_2_7:HBM[2]
CLFLAGS += --sp vadd_1.in0_3_0:HBM[3]
CLFLAGS += --sp vadd_1.in0_3_1:HBM[3]
CLFLAGS += --sp vadd_1.in0_3_2:HBM[3]
CLFLAGS += --sp vadd_1.in0_3_3:HBM[3]
CLFLAGS += --sp vadd_1.in0_3_4:HBM[3]
CLFLAGS += --sp vadd_1.in0_3_5:HBM[3]
CLFLAGS += --sp vadd_1.in0_3_6:HBM[3]
CLFLAGS += --sp vadd_1.in0_3_7:HBM[3]
CLFLAGS += --sp vadd_1.in0_4_0:HBM[4]
CLFLAGS += --sp vadd_1.in0_4_1:HBM[4]
CLFLAGS += --sp vadd_1.in0_4_2:HBM[4]
CLFLAGS += --sp vadd_1.in0_4_3:HBM[4]
CLFLAGS += --sp vadd_1.in0_4_4:HBM[4]
CLFLAGS += --sp vadd_1.in0_4_5:HBM[4]
CLFLAGS += --sp vadd_1.in0_4_6:HBM[4]
CLFLAGS += --sp vadd_1.in0_4_7:HBM[4]
CLFLAGS += --sp vadd_1.in0_5_0:HBM[5]
CLFLAGS += --sp vadd_1.in0_5_1:HBM[5]
CLFLAGS += --sp vadd_1.in0_5_2:HBM[5]
CLFLAGS += --sp vadd_1.in0_5_3:HBM[5]
CLFLAGS += --sp vadd_1.in0_5_4:HBM[5]
CLFLAGS += --sp vadd_1.in0_5_5:HBM[5]
CLFLAGS += --sp vadd_1.in0_5_6:HBM[5]
CLFLAGS += --sp vadd_1.in0_5_7:HBM[5]
CLFLAGS += --sp vadd_1.in0_6_0:HBM[6]
CLFLAGS += --sp vadd_1.in0_6_1:HBM[6]
CLFLAGS += --sp vadd_1.in0_6_2:HBM[6]
CLFLAGS += --sp vadd_1.in0_6_3:HBM[6]
CLFLAGS += --sp vadd_1.in0_6_4:HBM[6]
CLFLAGS += --sp vadd_1.in0_6_5:HBM[6]
CLFLAGS += --sp vadd_1.in0_6_6:HBM[6]
CLFLAGS += --sp vadd_1.in0_6_7:HBM[6]
CLFLAGS += --sp vadd_1.in0_7_0:HBM[7]
CLFLAGS += --sp vadd_1.in0_7_1:HBM[7]
CLFLAGS += --sp vadd_1.in0_7_2:HBM[7]
CLFLAGS += --sp vadd_1.in0_7_3:HBM[7]
CLFLAGS += --sp vadd_1.in0_7_4:HBM[7]
CLFLAGS += --sp vadd_1.in0_7_5:HBM[7]
CLFLAGS += --sp vadd_1.in0_7_6:HBM[7]
CLFLAGS += --sp vadd_1.in0_7_7:HBM[7]
CLFLAGS += --sp vadd_1.in1_0_0:HBM[8]
CLFLAGS += --sp vadd_1.in1_0_1:HBM[8]
CLFLAGS += --sp vadd_1.in1_0_2:HBM[8]
CLFLAGS += --sp vadd_1.in1_0_3:HBM[8]
CLFLAGS += --sp vadd_1.in1_0_4:HBM[8]
CLFLAGS += --sp vadd_1.in1_0_5:HBM[8]
CLFLAGS += --sp vadd_1.in1_0_6:HBM[8]
CLFLAGS += --sp vadd_1.in1_0_7:HBM[8]
CLFLAGS += --sp vadd_1.in1_1_0:HBM[9]
CLFLAGS += --sp vadd_1.in1_1_1:HBM[9]
CLFLAGS += --sp vadd_1.in1_1_2:HBM[9]
CLFLAGS += --sp vadd_1.in1_1_3:HBM[9]
CLFLAGS += --sp vadd_1.in1_1_4:HBM[9]
CLFLAGS += --sp vadd_1.in1_1_5:HBM[9]
CLFLAGS += --sp vadd_1.in1_1_6:HBM[9]
CLFLAGS += --sp vadd_1.in1_1_7:HBM[9]
CLFLAGS += --sp vadd_1.in1_2_0:HBM[10]
CLFLAGS += --sp vadd_1.in1_2_1:HBM[10]
CLFLAGS += --sp vadd_1.in1_2_2:HBM[10]
CLFLAGS += --sp vadd_1.in1_2_3:HBM[10]
CLFLAGS += --sp vadd_1.in1_2_4:HBM[10]
CLFLAGS += --sp vadd_1.in1_2_5:HBM[10]
CLFLAGS += --sp vadd_1.in1_2_6:HBM[10]
CLFLAGS += --sp vadd_1.in1_2_7:HBM[10]
CLFLAGS += --sp vadd_1.in1_3_0:HBM[11]
CLFLAGS += --sp vadd_1.in1_3_1:HBM[11]
CLFLAGS += --sp vadd_1.in1_3_2:HBM[11]
CLFLAGS += --sp vadd_1.in1_3_3:HBM[11]
CLFLAGS += --sp vadd_1.in1_3_4:HBM[11]
CLFLAGS += --sp vadd_1.in1_3_5:HBM[11]
CLFLAGS += --sp vadd_1.in1_3_6:HBM[11]
CLFLAGS += --sp vadd_1.in1_3_7:HBM[11]
CLFLAGS += --sp vadd_1.in1_4_0:HBM[12]
CLFLAGS += --sp vadd_1.in1_4_1:HBM[12]
CLFLAGS += --sp vadd_1.in1_4_2:HBM[12]
CLFLAGS += --sp vadd_1.in1_4_3:HBM[12]
CLFLAGS += --sp vadd_1.in1_4_4:HBM[12]
CLFLAGS += --sp vadd_1.in1_4_5:HBM[12]
CLFLAGS += --sp vadd_1.in1_4_6:HBM[12]
CLFLAGS += --sp vadd_1.in1_4_7:HBM[12]
CLFLAGS += --sp vadd_1.in1_5_0:HBM[13]
CLFLAGS += --sp vadd_1.in1_5_1:HBM[13]
CLFLAGS += --sp vadd_1.in1_5_2:HBM[13]
CLFLAGS += --sp vadd_1.in1_5_3:HBM[13]
CLFLAGS += --sp vadd_1.in1_5_4:HBM[13]
CLFLAGS += --sp vadd_1.in1_5_5:HBM[13]
CLFLAGS += --sp vadd_1.in1_5_6:HBM[13]
CLFLAGS += --sp vadd_1.in1_5_7:HBM[13]
CLFLAGS += --sp vadd_1.in1_6_0:HBM[14]
CLFLAGS += --sp vadd_1.in1_6_1:HBM[14]
CLFLAGS += --sp vadd_1.in1_6_2:HBM[14]
CLFLAGS += --sp vadd_1.in1_6_3:HBM[14]
CLFLAGS += --sp vadd_1.in1_6_4:HBM[14]
CLFLAGS += --sp vadd_1.in1_6_5:HBM[14]
CLFLAGS += --sp vadd_1.in1_6_6:HBM[14]
CLFLAGS += --sp vadd_1.in1_6_7:HBM[14]
CLFLAGS += --sp vadd_1.in1_7_0:HBM[15]
CLFLAGS += --sp vadd_1.in1_7_1:HBM[15]
CLFLAGS += --sp vadd_1.in1_7_2:HBM[15]
CLFLAGS += --sp vadd_1.in1_7_3:HBM[15]
CLFLAGS += --sp vadd_1.in1_7_4:HBM[15]
CLFLAGS += --sp vadd_1.in1_7_5:HBM[15]
CLFLAGS += --sp vadd_1.in1_7_6:HBM[15]
CLFLAGS += --sp vadd_1.in1_7_7:HBM[15]
CLFLAGS += --sp vadd_1.out0_0_0:HBM[8]
CLFLAGS += --sp vadd_1.out0_0_1:HBM[9]
CLFLAGS += --sp vadd_1.out0_0_2:HBM[10]
CLFLAGS += --sp vadd_1.out0_0_3:HBM[11]
CLFLAGS += --sp vadd_1.out0_0_4:HBM[12]
CLFLAGS += --sp vadd_1.out0_0_5:HBM[13]
CLFLAGS += --sp vadd_1.out0_0_6:HBM[14]
CLFLAGS += --sp vadd_1.out0_0_7:HBM[15]
CLFLAGS += --sp vadd_1.out0_1_0:HBM[8]
CLFLAGS += --sp vadd_1.out0_1_1:HBM[9]
CLFLAGS += --sp vadd_1.out0_1_2:HBM[10]
CLFLAGS += --sp vadd_1.out0_1_3:HBM[11]
CLFLAGS += --sp vadd_1.out0_1_4:HBM[12]
CLFLAGS += --sp vadd_1.out0_1_5:HBM[13]
CLFLAGS += --sp vadd_1.out0_1_6:HBM[14]
CLFLAGS += --sp vadd_1.out0_1_7:HBM[15]
CLFLAGS += --sp vadd_1.out0_2_0:HBM[8]
CLFLAGS += --sp vadd_1.out0_2_1:HBM[9]
CLFLAGS += --sp vadd_1.out0_2_2:HBM[10]
CLFLAGS += --sp vadd_1.out0_2_3:HBM[11]
CLFLAGS += --sp vadd_1.out0_2_4:HBM[12]
CLFLAGS += --sp vadd_1.out0_2_5:HBM[13]
CLFLAGS += --sp vadd_1.out0_2_6:HBM[14]
CLFLAGS += --sp vadd_1.out0_2_7:HBM[15]
CLFLAGS += --sp vadd_1.out0_3_0:HBM[8]
CLFLAGS += --sp vadd_1.out0_3_1:HBM[9]
CLFLAGS += --sp vadd_1.out0_3_2:HBM[10]
CLFLAGS += --sp vadd_1.out0_3_3:HBM[11]
CLFLAGS += --sp vadd_1.out0_3_4:HBM[12]
CLFLAGS += --sp vadd_1.out0_3_5:HBM[13]
CLFLAGS += --sp vadd_1.out0_3_6:HBM[14]
CLFLAGS += --sp vadd_1.out0_3_7:HBM[15]
CLFLAGS += --sp vadd_1.out0_4_0:HBM[8]
CLFLAGS += --sp vadd_1.out0_4_1:HBM[9]
CLFLAGS += --sp vadd_1.out0_4_2:HBM[10]
CLFLAGS += --sp vadd_1.out0_4_3:HBM[11]
CLFLAGS += --sp vadd_1.out0_4_4:HBM[12]
CLFLAGS += --sp vadd_1.out0_4_5:HBM[13]
CLFLAGS += --sp vadd_1.out0_4_6:HBM[14]
CLFLAGS += --sp vadd_1.out0_4_7:HBM[15]
CLFLAGS += --sp vadd_1.out0_5_0:HBM[8]
CLFLAGS += --sp vadd_1.out0_5_1:HBM[9]
CLFLAGS += --sp vadd_1.out0_5_2:HBM[10]
CLFLAGS += --sp vadd_1.out0_5_3:HBM[11]
CLFLAGS += --sp vadd_1.out0_5_4:HBM[12]
CLFLAGS += --sp vadd_1.out0_5_5:HBM[13]
CLFLAGS += --sp vadd_1.out0_5_6:HBM[14]
CLFLAGS += --sp vadd_1.out0_5_7:HBM[15]
CLFLAGS += --sp vadd_1.out0_6_0:HBM[8]
CLFLAGS += --sp vadd_1.out0_6_1:HBM[9]
CLFLAGS += --sp vadd_1.out0_6_2:HBM[10]
CLFLAGS += --sp vadd_1.out0_6_3:HBM[11]
CLFLAGS += --sp vadd_1.out0_6_4:HBM[12]
CLFLAGS += --sp vadd_1.out0_6_5:HBM[13]
CLFLAGS += --sp vadd_1.out0_6_6:HBM[14]
CLFLAGS += --sp vadd_1.out0_6_7:HBM[15]
CLFLAGS += --sp vadd_1.out0_7_0:HBM[8]
CLFLAGS += --sp vadd_1.out0_7_1:HBM[9]
CLFLAGS += --sp vadd_1.out0_7_2:HBM[10]
CLFLAGS += --sp vadd_1.out0_7_3:HBM[11]
CLFLAGS += --sp vadd_1.out0_7_4:HBM[12]
CLFLAGS += --sp vadd_1.out0_7_5:HBM[13]
CLFLAGS += --sp vadd_1.out0_7_6:HBM[14]
CLFLAGS += --sp vadd_1.out0_7_7:HBM[15]
CLFLAGS += --sp vadd_1.out1_0_0:HBM[0]
CLFLAGS += --sp vadd_1.out1_0_1:HBM[1]
CLFLAGS += --sp vadd_1.out1_0_2:HBM[2]
CLFLAGS += --sp vadd_1.out1_0_3:HBM[3]
CLFLAGS += --sp vadd_1.out1_0_4:HBM[4]
CLFLAGS += --sp vadd_1.out1_0_5:HBM[5]
CLFLAGS += --sp vadd_1.out1_0_6:HBM[6]
CLFLAGS += --sp vadd_1.out1_0_7:HBM[7]
CLFLAGS += --sp vadd_1.out1_1_0:HBM[0]
CLFLAGS += --sp vadd_1.out1_1_1:HBM[1]
CLFLAGS += --sp vadd_1.out1_1_2:HBM[2]
CLFLAGS += --sp vadd_1.out1_1_3:HBM[3]
CLFLAGS += --sp vadd_1.out1_1_4:HBM[4]
CLFLAGS += --sp vadd_1.out1_1_5:HBM[5]
CLFLAGS += --sp vadd_1.out1_1_6:HBM[6]
CLFLAGS += --sp vadd_1.out1_1_7:HBM[7]
CLFLAGS += --sp vadd_1.out1_2_0:HBM[0]
CLFLAGS += --sp vadd_1.out1_2_1:HBM[1]
CLFLAGS += --sp vadd_1.out1_2_2:HBM[2]
CLFLAGS += --sp vadd_1.out1_2_3:HBM[3]
CLFLAGS += --sp vadd_1.out1_2_4:HBM[4]
CLFLAGS += --sp vadd_1.out1_2_5:HBM[5]
CLFLAGS += --sp vadd_1.out1_2_6:HBM[6]
CLFLAGS += --sp vadd_1.out1_2_7:HBM[7]
CLFLAGS += --sp vadd_1.out1_3_0:HBM[0]
CLFLAGS += --sp vadd_1.out1_3_1:HBM[1]
CLFLAGS += --sp vadd_1.out1_3_2:HBM[2]
CLFLAGS += --sp vadd_1.out1_3_3:HBM[3]
CLFLAGS += --sp vadd_1.out1_3_4:HBM[4]
CLFLAGS += --sp vadd_1.out1_3_5:HBM[5]
CLFLAGS += --sp vadd_1.out1_3_6:HBM[6]
CLFLAGS += --sp vadd_1.out1_3_7:HBM[7]
CLFLAGS += --sp vadd_1.out1_4_0:HBM[0]
CLFLAGS += --sp vadd_1.out1_4_1:HBM[1]
CLFLAGS += --sp vadd_1.out1_4_2:HBM[2]
CLFLAGS += --sp vadd_1.out1_4_3:HBM[3]
CLFLAGS += --sp vadd_1.out1_4_4:HBM[4]
CLFLAGS += --sp vadd_1.out1_4_5:HBM[5]
CLFLAGS += --sp vadd_1.out1_4_6:HBM[6]
CLFLAGS += --sp vadd_1.out1_4_7:HBM[7]
CLFLAGS += --sp vadd_1.out1_5_0:HBM[0]
CLFLAGS += --sp vadd_1.out1_5_1:HBM[1]
CLFLAGS += --sp vadd_1.out1_5_2:HBM[2]
CLFLAGS += --sp vadd_1.out1_5_3:HBM[3]
CLFLAGS += --sp vadd_1.out1_5_4:HBM[4]
CLFLAGS += --sp vadd_1.out1_5_5:HBM[5]
CLFLAGS += --sp vadd_1.out1_5_6:HBM[6]
CLFLAGS += --sp vadd_1.out1_5_7:HBM[7]
CLFLAGS += --sp vadd_1.out1_6_0:HBM[0]
CLFLAGS += --sp vadd_1.out1_6_1:HBM[1]
CLFLAGS += --sp vadd_1.out1_6_2:HBM[2]
CLFLAGS += --sp vadd_1.out1_6_3:HBM[3]
CLFLAGS += --sp vadd_1.out1_6_4:HBM[4]
CLFLAGS += --sp vadd_1.out1_6_5:HBM[5]
CLFLAGS += --sp vadd_1.out1_6_6:HBM[6]
CLFLAGS += --sp vadd_1.out1_6_7:HBM[7]
CLFLAGS += --sp vadd_1.out1_7_0:HBM[0]
CLFLAGS += --sp vadd_1.out1_7_1:HBM[1]
CLFLAGS += --sp vadd_1.out1_7_2:HBM[2]
CLFLAGS += --sp vadd_1.out1_7_3:HBM[3]
CLFLAGS += --sp vadd_1.out1_7_4:HBM[4]
CLFLAGS += --sp vadd_1.out1_7_5:HBM[5]
CLFLAGS += --sp vadd_1.out1_7_6:HBM[6]
CLFLAGS += --sp vadd_1.out1_7_7:HBM[7]

CLFLAGS += --report_level 2
CLFLAGS += -O3
CLFLAGS += --vivado.prop=run.impl_1.STRATEGY=Performance_EarlyBlockPlacement 

EXECUTABLE = host
CMD_ARGS = $(BUILD_DIR)/vadd.xclbin
EMCONFIG_DIR = $(TEMP_DIR)
EMU_DIR = $(SDCARD)/data/emulation

BINARY_CONTAINERS += $(BUILD_DIR)/vadd.xclbin
BINARY_CONTAINER_vadd_OBJS += $(TEMP_DIR)/vadd.xo

CP = cp -rf

.PHONY: all clean cleanall docs emconfig
all: check-devices $(EXECUTABLE) $(BINARY_CONTAINERS) emconfig sd_card

.PHONY: exe
exe: $(EXECUTABLE)

.PHONY: build
build: $(BINARY_CONTAINERS)

# Building kernel
$(TEMP_DIR)/vadd.xo: src/vadd.cpp
	mkdir -p $(TEMP_DIR)
	$(VPP) $(CLFLAGS) --temp_dir $(TEMP_DIR) -c -k vadd -I'$(<D)' -o'$@' '$<'
$(BUILD_DIR)/vadd.xclbin: $(BINARY_CONTAINER_vadd_OBJS)
	mkdir -p $(BUILD_DIR)
	$(VPP) $(CLFLAGS) --temp_dir $(BUILD_DIR) -l $(LDCLFLAGS) -o'$@' $(+)

# Building Host
$(EXECUTABLE): check-xrt $(HOST_SRCS) $(HOST_HDRS)
	$(CXX) $(CXXFLAGS) $(HOST_SRCS) $(HOST_HDRS) -o '$@' $(LDFLAGS)

emconfig:$(EMCONFIG_DIR)/emconfig.json
$(EMCONFIG_DIR)/emconfig.json:
	emconfigutil --platform $(DEVICE) --od $(EMCONFIG_DIR)

check: all
ifeq ($(TARGET),$(filter $(TARGET),sw_emu hw_emu))
ifeq ($(HOST_ARCH), x86)
	$(CP) $(EMCONFIG_DIR)/emconfig.json .
	XCL_EMULATION_MODE=$(TARGET) ./$(EXECUTABLE) $(BUILD_DIR)/vadd.xclbin
else
	mkdir -p $(EMU_DIR)
	$(CP) $(XILINX_VITIS)/data/emulation/unified $(EMU_DIR)
	mkfatimg $(SDCARD) $(SDCARD).img 500000
	launch_emulator -no-reboot -runtime ocl -t $(TARGET) -sd-card-image $(SDCARD).img -device-family $(DEV_FAM)
endif
else
ifeq ($(HOST_ARCH), x86)
	./$(EXECUTABLE) $(BUILD_DIR)/vadd.xclbin
endif
endif
ifeq ($(HOST_ARCH), x86)
	perf_analyze profile -i profile_summary.csv -f html
endif

sd_card: $(EXECUTABLE) $(BINARY_CONTAINERS) emconfig
ifneq ($(HOST_ARCH), x86)
	mkdir -p $(SDCARD)/$(BUILD_DIR)
	$(CP) $(B_NAME)/sw/$(XSA)/boot/generic.readme $(B_NAME)/sw/$(XSA)/xrt/image/* xrt.ini $(EXECUTABLE) $(SDCARD)
	$(CP) $(BUILD_DIR)/*.xclbin $(SDCARD)/$(BUILD_DIR)/
ifeq ($(TARGET),$(filter $(TARGET),sw_emu hw_emu))
	$(ECHO) 'cd /mnt/' >> $(SDCARD)/init.sh
	$(ECHO) 'export XILINX_VITIS=$$PWD' >> $(SDCARD)/init.sh
	$(ECHO) 'export XCL_EMULATION_MODE=$(TARGET)' >> $(SDCARD)/init.sh
	$(ECHO) './$(EXECUTABLE) $(CMD_ARGS)' >> $(SDCARD)/init.sh
	$(ECHO) 'reboot' >> $(SDCARD)/init.sh
else
	[ -f $(SDCARD)/BOOT.BIN ] && echo "INFO: BOOT.BIN already exists" || $(CP) $(BUILD_DIR)/sd_card/BOOT.BIN $(SDCARD)/
	$(ECHO) './$(EXECUTABLE) $(CMD_ARGS)' >> $(SDCARD)/init.sh
endif
endif

# Cleaning stuff
clean:
	-$(RMDIR) $(EXECUTABLE) $(XCLBIN)/{*sw_emu*,*hw_emu*} 
	-$(RMDIR) profile_* TempConfig system_estimate.xtxt *.rpt *.csv 
	-$(RMDIR) src/*.ll *v++* .Xil emconfig.json dltmp* xmltmp* *.log *.jou *.wcfg *.wdb

cleanall: clean
	-$(RMDIR) build_dir* sd_card*
	-$(RMDIR) _x.* *xclbin.run_summary qemu-memory-_* emulation/ _vimage/ pl* start_simulation.sh *.xclbin

