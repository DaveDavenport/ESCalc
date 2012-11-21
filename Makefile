PROGRAM=hconvert
PREFIX?=/usr/local/

SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:%.cc=%.o)

READLINE_LIBS=-lreadline
MUPARSER_LIBS=$(shell pkg-config --libs muparser)

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $^

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(MUPARSER_LIBS) $(READLINE_LIBS)


clean:
	rm -f $(PROGRAM)

install: $(PROGRAM)
	install $(PROGRAM) $(PREFIX)/bin/
