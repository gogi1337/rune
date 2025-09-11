CXX := g++
CXXFLAGS := -std=c++23 -Wall
SRC := $(shell find src -name "*.cpp")
OBJ := $(patsubst src/%.cpp,build/%.o,$(SRC))
TARGET := rune
LIBS := `pkg-config --cflags --libs glfw3` -lvulkan -Ivendor/glm

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: clean
