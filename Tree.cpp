#include "Tree.h"

Tree::Tree(int depth)
{
    root = CreateNodes(depth);
}

Tree::~Tree()
{
    DestroyNodes(root);
}

TreeNode* Tree::CreateNodes(int depth) 
{
    TreeNode* node = new TreeNode();
    if (depth > 0)
    {
        node->SetLeftNode(CreateNodes(depth - 1));
        node->SetRightNode(CreateNodes(depth - 1));        
    } else {
        node->SetLeftNode(nullptr);
        node->SetRightNode(nullptr);        
    }
    return node;
}

void Tree::DestroyNodes(TreeNode* root)
{
    if (root->GetLeftNode() != nullptr)
    {       
        DestroyNodes(root->GetLeftNode());     
        DestroyNodes(root->GetRightNode());
    }
    delete root;
}

long Tree::CalcCheckSum(TreeNode* root)
{
    long checkSum = 0;
    if (root->GetLeftNode() != nullptr)
    {
        checkSum = CalcCheckSum(root->GetLeftNode()) + CalcCheckSum(root->GetRightNode());
    }
    return checkSum + 1;
}

long Tree::CheckSum()
{
    return CalcCheckSum(root);
}

