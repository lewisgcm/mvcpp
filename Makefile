BUILD_DIR   = build/
SOURCE_DIR  = source
TEST_DIR    = test
DOCS_DIR    = documentation
EXAMPLE_DIR = examples
INCLUDES    = -I include -I submodules/json/src
LINKFLAGS   = -Wl,--no-as-needed -lcppunit -lboost_system -lpthread
BUILD_NAME  = mvcpp

CXX = g++-4.9
CXXFLAGS = -Werror -std=c++11 $(INCLUDES) $(LINKFLAGS) -O3

SOURCES  = $(shell find $(SOURCE_DIR) -type f -name '*.cpp' | cut -sd / -f 2-)
OBJECTS  = $(foreach x, $(basename $(SOURCES)), $(BUILD_DIR)$(x).o)
TESTS_S  = $(shell find $(TEST_DIR) -type f -name '*.cpp')
TESTS_O  = $(TESTS_S:%.cpp=%.o)

compile: $(OBJECTS)

build: compile
	$(CXX) $(CXXFLAGS) $(OBJECTS) -shared -Wl,-soname,lib$(BUILD_NAME).so -o lib$(BUILD_NAME).so

.PHONY: examples
examples:
	$(CXX) $(CXXFLAGS) -L`pwd`/ -lboost_system -l$(BUILD_NAME) $(EXAMPLE_DIR)/file-server.cpp -o examples/file-server

run:
	@export LD_LIBRARY_PATH=`pwd`/; ./examples/file-server

install: build
	cp lib$(BUILD_NAME).so /usr/lib

test: build $(TESTS_O)
	@$(CXX) $(CXXFLAGS) $(TESTS_O) -L`pwd`/ -lboost_system -l$(BUILD_NAME) -o testRunner -I $(TEST_DIR) $(TEST_DIR)/test.c
	@export LD_LIBRARY_PATH=`pwd`/; ./testRunner; rm testRunner

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
	@rm -f lib$(BUILD_NAME).so
	@rm -r test_*