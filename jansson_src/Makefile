BUILD := $(ROOT)/build
DIST := $(ROOT)/dist

CXX=g++
CC=gcc
$(info CXXFLAGS $(CXXFLAGS))
$(info CFLAGS $(CFLAGS))

LDFLAGS := -fpic -lpthread 

CXXFLAGS :=	$(CXXFLAGS) -I./
#LDFLAGS := -fpic -lpthread
CFLAGS := $(CFLAGS) -I./

JSON_SRC := $(shell  find . -name '*.c' -a -not -name 'test*')
JSON_TEST_SRC := $(shell  find . -name '*.c*' -a -name 'test*')

JSON_OBJS := $(patsubst %.c,$(BUILD)/jansson/%.o,$(JSON_SRC))

$(info JSON_OBJS $(JSON_OBJS))


#.SUFFIXES: .cc

$(BUILD)/jansson/%.o: %.c
	@echo "Processing " $^ " for " $(@D) 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@ 

$(BUILD)/jansson/%.o: %.cc
	@echo "Processing " $^ " for " $(@D) 
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $^ -o $@ 



all: $(DIST)/libjansson.a $(DIST)/libjansson.so $(BUILD)/test_jansson1

$(BUILD)/test_jansson1: $(BUILD)/jansson/test1.o
	$(CXX) -o $@ $^ -L$(DIST) -Wl,-Bstatic -ljansson -lboost_locale -lboost_system -Wl,-Bdynamic 


$(DIST)/libjansson.a: $(JSON_OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^

$(DIST)/libjansson.so: $(JSON_OBJS)
	@mkdir -p $(@D)
	$(CC) -shared -o $@ $^ $(LDFLAGS)
	
clean:
	rm -rf $(BUILD)/libjansson.a $(JSON_OBJS)