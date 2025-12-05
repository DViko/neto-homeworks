
LIB_DIR := include
SRC_DIR := src
BUILD_DIR := build

CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -O2 -g -I$(LIB_DIR)
LD := $(CXX)
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt

TARGET := $(BUILD_DIR)/life_app

SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(LIB_DIR)/*.cpp)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY:
	all clean run