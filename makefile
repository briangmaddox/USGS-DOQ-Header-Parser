#  $Id: makefile,v 1.1.1.1 2002-02-19 19:08:25 bmaddox Exp $
prefix		=	/home/bmaddox
exec_prefix	=	${prefix}
host_os		=	linux
srcdir		=	.
top_srcdir	=	.
enable_debug	=	no

# Where to find includes for libraries that DOQParserLib depends on.
INCPATHS = -I$(prefix)/include

ifeq ($(enable_debug),yes)
DEBUG= -g -Wall
else
DEBUG= -O2
endif

ifeq ($(host_os), linux)
LIBPATH=${prefix}/lib
else
LIBPATH=$(prefix}/lib/dgux
endif

CC= gcc
CXX= g++
CXXFLAGS=$(DEBUG) $(INCPATHS)
RANLIB=ranlib

SRCS= DOQParser.cc


OBJS=$(SRCS:.cc=.o)


all: libDOQParser.a 
	@echo "Done compiling libDOQParser.a"

libDOQParser.a: $(OBJS)
	ar ru libDOQParser.a $(OBJS)

parsedoq: parsedoq.cc
	$(CXX) $(CXXFLAGS) -L$(LIBPATH) parsedoq.cc -o parsedoq -lDOQParser

install: DOQParser.h libDOQParser.a
	cp DOQParser.h $(prefix)/include/DOQParser
	cp libDOQParser.a $(LIBPATH)

clean::
	rm -f $(OBJS) *.a core parsedoq


