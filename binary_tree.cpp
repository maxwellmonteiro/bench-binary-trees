#include "Tree.h"
#include <iostream>
#include <string>

#define MAXIMUM_LINE_WIDTH  60

using namespace std;

intnative_t GetArgAsLong(int argc, char** argv, uint16_t index)
{
    if (argc > index)
        return std::stoi(argv[index]);
    return 0;
}


int main(int argc, char** argv)
{
    intnative_t min_depth, max_depth;

    min_depth = 4;
    max_depth = GetArgAsLong(argc, argv, 1);

    if (max_depth < min_depth + 2)
        max_depth = min_depth + 2;

    Tree* stretched_tree = new Tree(max_depth + 1);
    cout << "stretch tree of depth " << max_depth + 1 << "\t check: " << stretched_tree->CheckSum() << endl;
    delete stretched_tree;

    Tree* long_live_tree = new Tree(max_depth);

    char output_buffer[max_depth + 1][MAXIMUM_LINE_WIDTH + 1];    
    intnative_t curr_depth;
    #pragma omp parallel for
    for(curr_depth = min_depth; curr_depth <= max_depth; curr_depth += 2) {
        intnative_t iterations = 1 << (max_depth - curr_depth + min_depth);      
                
        intnative_t total_checksum = 0;
        for(intnative_t i = 1; i <= iterations; ++i) {
            // Create a binary tree of depth current_tree_depth
            Tree* const tree = new Tree(curr_depth);
            total_checksum += tree->CheckSum();
            delete tree;
        }      

        // Record the statistics for the trees of depth current_tree_depth.       
        sprintf(output_buffer[curr_depth], "%llu\t trees of depth %llu\t check: %llu\n", iterations, curr_depth, total_checksum);
    }

    // Print the statistics for all of the various tree depths.
    for(curr_depth = min_depth; curr_depth <= max_depth; curr_depth += 2)
      cout << output_buffer[curr_depth];

    // Compute the checksum of the long-lived binary tree that we created
    // earlier, print the statistics, and then delete the memory pool.
    cout << "long lived tree of depth " << max_depth << "\t check: " << long_live_tree->CheckSum() << endl;

    delete long_live_tree;

    return 0; 
}