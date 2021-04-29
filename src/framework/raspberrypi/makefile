# Compiler flags
CXXFLAGS = -DBGT60_FRAMEWORK=BGT60_FRMWK_RPI -DBGT60_LOGGER_ENABLED=0 

# System paths
SYS_INC_DIR = /usr/include
SYS_LIB_DIR = /usr/local/lib

# Library paths
CORELIB_DIR = ../../corelib
PAL_DIR = pal
PALI_DIR = ../../pal
WRAPPER_DIR = wrapper
CONFIG_DIR = ../../config
BUILD_DIR = ../../../build

### src folder structure ###
# src
# ├── config
# │   └── ...
# ├── corelib
# │   └── ...
# ├── framework
# │   └── raspberrypi
# │       ├── examples
# │       │   └── ...
# │       ├── makefile <- this file
# │       ├── pal
# │       │   └── ...
# │       ├── wrapper
# │       │   └── ...
# │       └── ...
# ├── pal
# │   └── ...
# └── ...

# --- DO NOT CHANGE BELOW THIS LINE ---

EXAMPLES := $(basename $(wildcard examples/*.cpp))
CORELIB_SRC := $(shell find $(CORELIB_DIR) -type f -name *.cpp)
PAL_SRC := $(shell find $(PAL_DIR) -type f -name *.cpp)
WRAPPER_SRC := $(shell find $(WRAPPER_DIR) -type f -name *.cpp ! -name *-pybind.cpp)
CORELIB_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(CORELIB_SRC:.cpp=.o)))
PAL_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(PAL_SRC:.cpp=.o)))
WRAPPER_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(WRAPPER_SRC:.cpp=.o)))
CXX_INC := $(addprefix -I, $(PAL_DIR) $(PALI_DIR) $(CONFIG_DIR) $(CORELIB_DIR) $(WRAPPER_DIR))
LIB_DIRS := $(CORELIB_DIR) $(PAL_DIR) $(WRAPPER_DIR)

.PHONY: default clean $(EXAMPLES)

default: examples/bgt60-MotionDetection

$(BUILD_DIR)/%.o: $(CORELIB_DIR)/%.cpp
	@mkdir -p $(@D)
	@g++ -c $(CXXFLAGS) -o $@ $< $(CXX_INC)

$(BUILD_DIR)/%.o: $(PAL_DIR)/%.cpp
	@mkdir -p $(@D)
	@g++ -c $(CXXFLAGS) -o $@ $< $(CXX_INC)

$(BUILD_DIR)/%.o: $(WRAPPER_DIR)/%.cpp
	@mkdir -p $(@D)
	@g++ -c $(CXXFLAGS) -o $@ $< $(CXX_INC)

$(EXAMPLES): $(CORELIB_OBJ) $(PAL_OBJ) $(WRAPPER_OBJ)
	@g++ -c $(CXXFLAGS) -o $(BUILD_DIR)/$(@F).o examples/$(@F).cpp $(CXX_INC)
	@g++ $(CXXFLAGS) -o $(BUILD_DIR)/$(@F) $(BUILD_DIR)/*.o -I$(SYS_INC_DIR) -L$(SYS_LIB_DIR) -lwiringPi
	@echo 'Type "$(BUILD_DIR)/$(@F)" to execute the example.'

clean:
	@rm -f $(BUILD_DIR)/*