# What works on command line:
# g++ -c -o rectang.o rectang.cpp
# g++ -c -o main.o main.cpp
# g++ -o rect main.o rectang.o

appname:=rev

CXX=g++
#CXX=clang++ --analyze
# -g generate source level debug information
CXXFLAGS=-g -Wall -std=c++11 -stdlib=libc++
# C pre-processor flags
#CPPFLAGS=-g $(shell root-config --cflags)
#SRC_DIR = ./src
#OBJ_DIR = ./bin/obj
#BIN_DIR = ./build/bin

SRCS=mylist.cpp
OBJS=$(patsubst %.cpp, %.o, $(SRCS))

all: $(appname)

$(appname): $(OBJS)
	@echo " Linking..."
	$(CXX) $(CXXFLAGS) -o $(appname) $(OBJS)

%.o: %.cpp
	@echo " Compiling $<"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o

distclean: clean
	rm -f *~ .depend
	rm -f $(appname)

#make_dirs:
#	mkdir -p $(OBJ_DIR)
#	mkdir -p $(BIN_DIR)
