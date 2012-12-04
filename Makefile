PROGRAM=escalc
PREFIX?=/usr/local/

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)

READLINE_LIBS=-lreadline
MUPARSER_LIBS=
MUPARSER_CFLAGS=-I.

%.o: %.cpp
	$(CXX) $(CFLAGS) $(MUPARSER_CFLAGS) -c -o $@ $^

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $@ $^ $(MUPARSER_LIBS) $(READLINE_LIBS)


clean:
	rm -f $(PROGRAM) $(OBJECTS)

install: $(PROGRAM)
	install $(PROGRAM) $(PREFIX)/bin/
