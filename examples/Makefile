CUSTOM_IS_CONSTEXPR_FLAG=0xAAEEEEEE
BINARY_STRING=\xEE\xEE\xEE\xAA

SRC= $(wildcard *.cpp)
EXAMPLES_ORIGINAL=$(patsubst %.cpp,%_original, $(SRC))
EXAMPLES=$(patsubst %_original,%,$(EXAMPLES_ORIGINAL))

CXX=g++
IN_CONSTEXPR_DIR=..
CXXFLAGS= -std=c++14 -O3
CXXFLAGS+= -I$(IN_CONSTEXPR_DIR)/include 
CXXFLAGS+= -DCUSTOM_IS_CONSTEXPR_FLAG=$(CUSTOM_IS_CONSTEXPR_FLAG)
DEPS= $(wildcard $(IN_CONSTEXPR_DIR)/include/*.hpp)

.PHONY: all clean
all: $(EXAMPLES_ORIGINAL) $(EXAMPLES)

clean: 
	-rm -f $(EXAMPLES_ORIGINAL) $(EXAMPLES)

%_original: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS)	$< -o $@

%: %_original
	sed "s/$(BINARY_STRING)/\x00\x00\x00\x00/g" $< > $@
	chmod +x $@




