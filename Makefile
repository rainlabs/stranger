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
OBJECTS    = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TARGET     = vad

### DEBUG ENVIRONMENT
debug: CXX     += -DDEBUG -g
debug: BUILDDIR = ./build/debug
debug: BINDIR   = ./bin/debug
###

### TEST ENVIRONMENT
test: LDFALGS += -lcppunit
test: MAIN     = TestRunner.cpp
test: BUILDDIR = ./build/test
test: BINDIR   = ./bin/test
test: INCLUDES+= -I./tests/
test: TSOURCES = $(shell find $(TESTDIR)/ -name '*.cpp')
test: OBJECTS  = $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TSOURCES)) $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
###

release: $(MAIN) $(SOURCES) $(BINDIR)/$(TARGET)
debug: release
test: $(MAIN) $(TSOURCES) $(SOURCES) $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(BUILDDIR)/$(MAIN:.cpp=.o) $(OBJECTS)
	$(CXX) $(LDFLAGS) $(BUILDDIR)/$(MAIN:.cpp=.o) $(OBJECTS) -o $@ -rdynamic $(LDYNAMIC)

$(OBJECTS): | $(BUILDDIR)

$(BUILDDIR):
	@mkdir -p $@

$(BUILDDIR)/$(MAIN:.cpp=.o): $(MAIN)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

clean:
	find -name *.o -delete && find bin/ -name $(TARGET) -delete
