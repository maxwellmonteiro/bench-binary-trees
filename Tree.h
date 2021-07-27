#include "TreeNode.h"

class Tree 
{
    private:
        int depth;
        TreeNode* root;
        TreeNode* CreateNodes(int depth);
        void DestroyNodes(TreeNode* root);
        long CalcCheckSum(TreeNode* root);
    public:
        Tree(int depth);
        ~Tree();
        long CheckSum();
        
};