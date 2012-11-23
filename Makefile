PROGRAM=escalc
PREFIX?=/usr/local/

SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:%.cc=%.o)

READLINE_LIBS=-lreadline
MUPARSER_LIBS=$(shell pkg-config --libs muparser)
MUPARSER_CFLAGS=$(shell pkg-config --cflags muparser)

%.o: %.cc
	$(CC) $(CFLAGS) $(MUPARSER_CFLAGS) -c -o $@ $^

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(MUPARSER_LIBS) $(READLINE_LIBS)


clean:
	rm -f $(PROGRAM) $(OBJECTS)

install: $(PROGRAM)
	install $(PROGRAM) $(PREFIX)/bin/
