#This makefile makes the examples from the first few chapters with Unity test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = myHead

#--- Inputs ----#
UNITY_HOME = /home/jonas/TDDEmbeddedC/tddec-code/code/unity.framework/
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .
PROJECT_TEST_DIR = test
CPP_PLATFORM = Gcc
UNITY_BUILD_HOME = /home/jonas/TDDEmbeddedC/tddec-code/code/unity.framework/extras/fixture/build

UNITY_CFLAGS += -DUNITY_OUTPUT_CHAR=UnityOutputCharSpy_OutputChar
UNITY_WARNINGFLAGS = -Wall -Werror -Wswitch-default
#UNITY_WARNINGFLAGS += -Wshadow

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/

TEST_SRC_DIRS = \
	$(PROJECT_TEST_DIR)\
	$(UNITY_HOME)/unity\
	$(UNITY_HOME)/src\
    $(UNITY_HOME)/extras/fixture/src\
    $(UNITY_HOME)/extras/fixture/test\

MOCKS_SRC_DIRS = \
	$(PROJECT_TEST_DIR)\

INCLUDE_DIRS =\
  .\
  $(UNITY_HOME)/src\
  $(UNITY_HOME)/extras/fixture/src\
  $(UNITY_HOME)/extras/fixture/test\
  /home/jonas/TDDEmbeddedC/tddec-code/code/unity/include/util\

include $(UNITY_BUILD_HOME)/MakefileWorker.mk
