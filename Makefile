CXX=gcc
RM=rm -f
INSTRUCT_SRCS = index.c
SRCS = search-engine.c
OBJS = $(SRCS:.c=.o) $(INSTRUCT_SRCS:.c=.o)
INSTRUCT_CPPFLAGS = -Wall -g
CPPFLAGS = -Wall -Werror -g
LDFLAGS = -Wall -Werror -lm
#LDLIBS=$(shell root-config --libs) -pthread
LDLIBS = -pthread
PROG=test

all: prog

prog: $(OBJS)
	gcc $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS) 

valgrind: $(OBJS)
	gcc $(LDFLAGS)  -o $(PROG) $(OBJS) $(LDLIBS) 
	valgrind --tool=memcheck --track-origins=yes \
	--leak-check=full  ./$(PROG)

depend: .depend .instruct_depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

.instruct_depend: $(INSTRUCT_SRCS)
	rm -f ./.depend
	$(CXX) $(INSTRUCT_CPPFLAGS) -MM $^>>./.instruct_depend;

clean:
	$(RM) $(OBJS) $(PROG)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
