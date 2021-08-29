#include <inttypes.h>
#include "TreeNode.h"


// intptr_t should be the native integer type on most sane systems.
typedef int64_t intnative_t;

class Tree 
{
    private:
        intnative_t depth;
        TreeNode* root;
        TreeNode* CreateNodes(intnative_t depth);
        void DestroyNodes(TreeNode* root);
        intnative_t CalcCheckSum(TreeNode* root);
    public:
        Tree(intnative_t depth);
        ~Tree();
        intnative_t CheckSum();
        
};