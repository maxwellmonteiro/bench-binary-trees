# _*_ Makefile _*_

CC = g++
CXX = g++
OBJECTS_CPP = binary_tree.o TreeNode.o Tree.o
SOURCES_C = binary_trees.c
CFLAGS = -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp -D_FILE_OFFSET_BITS=64
CXXFLAGS = $(CFLAGS)

all: binary_tree.clang binary_tree.cpplang

binary_tree.clang: $(SOURCES_C)
	$(CC) $(CFLAGS) $(SOURCES_C) -o $@ -lgomp -lm

binary_tree.cpplang: ${OBJECTS_CPP}
	$(CXX) ${OBJECTS_CPP} -o $@ -lgomp -lm

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

%.cpp: %.h
	

clean:
	rm -f *.o binary_tree.clang binary_tree.cpplang

