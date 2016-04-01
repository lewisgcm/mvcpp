BUILD_DIR  = build/
SOURCE_DIR = ../../source

INCLUDES   = -I ../../include
LINKFLAGS  = -Wl,--no-as-needed -lcppunit -ldl

SOURCES_D  = $(foreach x, $(basename $(SOURCES)), $(../../)$(x).cpp)
OBJECTS    = $(foreach x, $(basename $(SOURCES_D)), $(BUILD_DIR)$(x).o)

CXX = g++
CXXFLAGS = -Werror -std=gnu++11 $(INCLUDES) $(LINKFLAGS) -O3

build: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BUILD_NAME) $(BUILD_NAME).c

profile: CXXFLAGS += -pg
profile: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BUILD_NAME) $(BUILD_NAME).c
	./$(BUILD_NAME)
	gprof $(BUILD_NAME)

time: $(OBJECTS) build
	@echo "Starting timer"
	@(time ./$(BUILD_NAME)) &> $(BUILD_NAME).time
	@cat $(BUILD_NAME).time

cache-grind: build
	valgrind --tool=cachegrind ./$(BUILD_NAME)

call-grind: build
	valgrind --tool=callgrind ./$(BUILD_NAME)

$(BUILD_DIR)%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_NAME)
	@rm -f cachegrind.*
	@rm -f gmon.out 