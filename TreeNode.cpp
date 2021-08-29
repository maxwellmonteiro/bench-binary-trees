#include "TreeNode.h"

TreeNode::TreeNode()
{
    
}

TreeNode* TreeNode::GetLeftNode()
{
    return leftNode;
}

TreeNode* TreeNode::GetRightNode()
{
    return rightNode;
}

void TreeNode::SetLeftNode(TreeNode* node)
{
    leftNode = node;
}

void TreeNode::SetRightNode(TreeNode* node)
{
    rightNode = node;
}