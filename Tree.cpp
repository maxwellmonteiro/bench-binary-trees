#include "Tree.h"

Tree::Tree(intnative_t depth)
{
    root = CreateNodes(depth);
}

Tree::~Tree()
{
    DestroyNodes(root);
}

TreeNode* Tree::CreateNodes(intnative_t depth) 
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

intnative_t Tree::CalcCheckSum(TreeNode* root)
{
    intnative_t checkSum = 0;
    if (root->GetLeftNode() != nullptr)
    {
        checkSum = CalcCheckSum(root->GetLeftNode()) + CalcCheckSum(root->GetRightNode());
    }
    return checkSum + 1;
}

intnative_t Tree::CheckSum()
{
    return CalcCheckSum(root);
}

