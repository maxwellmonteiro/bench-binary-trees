class TreeNode 
{
    private:
        TreeNode* rightNode;
        TreeNode* leftNode;

    public:
        TreeNode();        
        TreeNode* GetRightNode();
        TreeNode* GetLeftNode();   
        void SetRightNode(TreeNode* node);
        void SetLeftNode(TreeNode* node);
};