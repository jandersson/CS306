# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
else ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q
	MKDIR = mkdir
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

PROJECT_ROOT= ./
UNITY_ROOT=/home/jonas/TDDEmbeddedC/tddec-code/code/unity.framework/
C_COMPILER=gcc
UNITY_BUILD_HOME = $(UNITY_ROOT)/extras/fixture/build


CFLAGS=-std=c11
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wswitch-default

TARGET_BASE1=myHead
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
SRC_FILES1=$(PROJECT_ROOT)lab1.c  test/myHeadTest.c
# SRC_FILES2=$(UNITY_ROOT)/src/unity.c src/ProductionCode2.c test/TestProductionC ode2.c test/test_runners/TestProductionCode2_Runner.c
INC_DIRS=-I$(UNITY_ROOT)/extras/fixture/src -I$(UNITY_ROOT)/extras/fixture/test -I$(UNITY_ROOT)/src
SYMBOLS=-DTEST

all: clean default

default:
#	ruby auto/generate_test_runner.rb test/TestProductionCode.c  test/test_runners/TestProductionCode_Runner.c
#	ruby auto/generate_test_runner.rb test/TestProductionCode2.c test/test_runners/TestProductionCode2_Runner.c
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)
	./$(TARGET1)

clean:
	$(CLEANUP)

