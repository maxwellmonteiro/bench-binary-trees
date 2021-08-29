// The Computer Language Benchmarks Game
// https://salsa.debian.org/benchmarksgame-team/benchmarksgame/
//
// Contributed by Jeremy Zerfas
// Based on the C++ program from Jon Harrop, Alex Mizrahi, and Bruno Coutinho.
// *reset*

// This controls the width of lines that are output by this program.
#define MAXIMUM_LINE_WIDTH  60

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// intptr_t should be the native integer type on most sane systems.
typedef int intnative_t;

typedef struct tree_node {
   struct tree_node* left_node;
   struct tree_node* right_node;
} tree_node;


// Create a binary tree of depth tree_depth in memory_Pool, set the root node's
// value to root_Node_Value, and finally return a pointer to the created binary
// tree.
static inline tree_node* create_tree(const intnative_t tree_depth) {
   tree_node* const root_node = (tree_node*) malloc(sizeof(tree_node));

   // If tree_depth is one or more then recursively call create_tree() in order
   // to create the left and right subtrees using 2*root_Node_Value-1 and
   // 2*root_Node_Value respectively as the root values for those subtrees.
   if (tree_depth > 0) {
      root_node->left_node = create_tree(tree_depth - 1);
      root_node->right_node = create_tree(tree_depth - 1);
   } else
      root_node->left_node = root_node->right_node = NULL;

   return root_node;
}


// Compute and return the checksum for the binary tree that has root_Node as the
// root node.
static inline intnative_t compute_tree_checksum(const tree_node* const root_node){
   // If there are subtrees then recursively call compute_tree_checksum() on
   // them and factor their values into the checksum, otherwise just return
   // the value of root_Node.
   if (root_node->left_node)
      return compute_tree_checksum(root_node->left_node) +
        compute_tree_checksum(root_node->right_node) + 1;
   
   return 1;
}

static inline void dealloc_tree(tree_node* const root_node) {   
   if (root_node->left_node) {
      dealloc_tree(root_node->left_node);
      dealloc_tree(root_node->right_node);
   }
   free(root_node);
}


int main(int argc, char** argv){
   
   // Set minimum_tree_depth to 4 and maximum_tree_depth to the maximum of what
   // was specified as the argument to the program and minimum_tree_depth+2.
   const intnative_t minimum_tree_depth = 4;
   intnative_t maximum_tree_depth = atoi(argv[1]);
   if(maximum_tree_depth < minimum_tree_depth + 2)
      maximum_tree_depth = minimum_tree_depth + 2;   

   // Create a memory pool, create a binary tree of depth maximum_tree_depth+1,
   // compute the checksum of the binary tree, print the statistics, and then
   // delete the memory pool.
   
   tree_node* stretched_tree = create_tree(maximum_tree_depth + 1);
   printf("stretch tree of depth %d\t check: %d\n",
     maximum_tree_depth + 1,
     compute_tree_checksum(stretched_tree));
   
   dealloc_tree(stretched_tree);

   // Create a memory pool and then create a long-lived binary tree of depth
   // maximum_tree_depth which will be left alone for a while while
   // more binary trees get allocated and deallocaited as required by the
   // rules. We'll finish working with this later.
   
   tree_node* long_lived_tree = create_tree(maximum_tree_depth);

   // Create a lot of binary trees in parallel of depths ranging from
   // minimum_tree_depth to maximum_tree_depth, compute and tally up all their
   // checksums, destroy the trees, and then record the statistics to
   // output_buffer[] so they can be displayed in order later.
   char output_buffer[maximum_tree_depth+1][MAXIMUM_LINE_WIDTH+1];
   intnative_t current_tree_depth;
   #pragma omp parallel for
   for(current_tree_depth = minimum_tree_depth; current_tree_depth <= maximum_tree_depth; current_tree_depth += 2) {
      intnative_t iterations = 1 << (maximum_tree_depth - current_tree_depth + minimum_tree_depth);      
      
      intnative_t i = 1, total_trees_checksum = 0;
      for(; i <= iterations; ++i) {
         // Create a binary tree of depth current_tree_depth
         tree_node* const tree_1 = create_tree(current_tree_depth);

         total_trees_checksum += compute_tree_checksum(tree_1);

         dealloc_tree(tree_1);
      }      

      // Record the statistics for the trees of depth current_tree_depth.
      sprintf(output_buffer[current_tree_depth],
        "%d\t trees of depth %d\t check: %d\n", iterations, current_tree_depth, total_trees_checksum);
   }

   // Print the statistics for all of the various tree depths.
   for(current_tree_depth = minimum_tree_depth; current_tree_depth <= maximum_tree_depth; current_tree_depth += 2)
      printf("%s", output_buffer[current_tree_depth]);

   // Compute the checksum of the long-lived binary tree that we created
   // earlier, print the statistics, and then delete the memory pool.
   printf("long lived tree of depth %d\t check: %d\n", maximum_tree_depth, compute_tree_checksum(long_lived_tree));

   dealloc_tree(long_lived_tree);
      
   
   return 0;
}