#include "Tree.h"
#include <iostream>
#include <string>

long GetArgAsLong(int argc, char** argv, int index)
{
    if (argc > index)
        return std::stoi(argv[index]);
    return 0;
}


int main(int argc, char** argv)
{
    long depth;
    depth = GetArgAsLong(argc, argv, 1);
    Tree* tree = new Tree(depth);
    std::cout << "checksum: " << tree->CheckSum() << std::endl;
    delete tree;   

    return 0; 
}