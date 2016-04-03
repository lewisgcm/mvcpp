BUILD_DIR  = build/
SOURCE_DIR = source
TEST_DIR   = test
DOCS_DIR   = documentation
INCLUDES   = -I include
LINKFLAGS  = -Wl,--no-as-needed -lcppunit -lboost_system -lpthread
BUILD_NAME = libmvcpp

CXX = g++-4.9
CXXFLAGS = -Werror -std=c++11 $(INCLUDES) $(LINKFLAGS) -O3

SOURCES  = $(shell find $(SOURCE_DIR) -type f -name '*.cpp' | cut -sd / -f 2-)
OBJECTS  = $(foreach x, $(basename $(SOURCES)), $(BUILD_DIR)$(x).o)
TESTS_S  = $(shell find $(TEST_DIR) -type f -name '*.cpp')
TESTS_O  = $(TESTS_S:%.cpp=%.o)

compile: $(OBJECTS)

build: compile
	$(CXX) $(CXXFLAGS) $(OBJECTS) -shared -Wl,-soname,$(BUILD_NAME).so.1 -o $(BUILD_NAME).so.1.0

examples: build

test: compile $(TESTS_O)
	@$(CXX) $(CXXFLAGS) $(TESTS_O) $(OBJECTS) -o testRunner -I $(TEST_DIR) $(TEST_DIR)/test.c
	@./testRunner
	@rm -r testRunner

docs:
	mkdir -p $(DOCS_DIR)/build
	cd $(DOCS_DIR); doxygen doxygen.cfg

$(BUILD_DIR)%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -I $(TEST_DIR) -c -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(TESTS_O)
	@rm -rf $(DOCS_DIR)/build
	@rm -f $(BUILD_NAME)