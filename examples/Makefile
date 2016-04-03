CXX         = g++-4.9
INCLUDES    = -I ../../include -I ../../submodules/json/src
LINKFLAGS   = -Wl,--no-as-needed -lcppunit -lboost_system -lpthread
CXXFLAGS    = -Werror -std=c++11 $(INCLUDES) $(LINKFLAGS) -O3
BUILD_NAME  = mvcpp

all:
	cd ../../; make build;
	$(CXX) $(CXXFLAGS) -L`pwd`/../../ -l$(BUILD_NAME) *.cpp -o example

run:
	@export LD_LIBRARY_PATH=`pwd`/../../; ./example