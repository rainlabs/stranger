CXX        = g++
CXXFLAGS   = -c -Wall -std=c++0x
LDFLAGS    = -lsndfile -lfftw3
LDYNAMIC   = -lspro
SRCDIR     = src
TESTDIR    = tests
SOURCES    = $(shell find $(SRCDIR)/ -name '*.cpp')
MAIN       = main.cpp
INCLUDES   = -I./include/
BUILDDIR   = ./build/release
BINDIR     = ./bin/release
OBJECTS    = $(BUILDDIR)/$(MAIN:.cpp=.o) $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TARGET     = vad

### DEBUG ENVIRONMENT
debug: CXX      += -DDEBUG -g
debug: BUILDDIR  = ./build/debug
debug: BINDIR    = ./bin/debug
###

### TEST ENVIRONMENT
test: LDFLAGS  += -lcppunit
test: MAIN      = TestRunner.cpp
test: BUILDDIR  = ./build/test
test: BINDIR    = ./bin/test
test: INCLUDES += -I./tests/
test: TSOURCES  = $(shell find $(TESTDIR)/ -name '*.cpp')
test: OBJECTS   = $(BUILDDIR)/$(MAIN:.cpp=.o) $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TSOURCES)) $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
#LDFLAGS  += -lcppunit
#MAIN      = TestRunner.cpp
#BUILDDIR  = ./build/test
#BINDIR    = ./bin/test
#INCLUDES += -I./tests/
#TSOURCES  = $(shell find $(TESTDIR)/ -name '*.cpp')
#OBJECTS   = $(BUILDDIR)/$(MAIN:.cpp=.o) $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TSOURCES)) $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
###

release: $(MAIN) $(SOURCES) $(BINDIR)/$(TARGET)
debug: release
test: $(MAIN) $(TSOURCES) $(SOURCES) $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ -rdynamic $(LDYNAMIC)

$(OBJECTS): | $(BUILDDIR)

$(BUILDDIR):
	@mkdir -p $@

$(BUILDDIR)/%.o: %.cpp
	@echo $<
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@echo $<
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

clean:
	find -name *.o -delete && find bin/ -name $(TARGET) -delete
