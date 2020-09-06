
#include "main.hpp"

// 字母异位词
bool isAnagram(string s, string t) 
{      
    int myTable[26] = { 0 };
    for (auto& ch : s) {
        myTable[ch - 'a']++;
    }
    
    for (auto& ch : t) {
        myTable[ch - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (myTable[i] != 0) {      
            return false;
        }
    }

    return true;
}

// 两数之和
vector<int> twoSum(vector<int>& nums, int target) 
{
    unordered_map<int, int> lists;
    for (int i = 0; i < nums.size(); i++) {
        if(lists.find(target - nums[i]) != lists.end()) {
            return vector<int>{lists[target - nums[i]], i};
        }
        lists.insert(pair<int, int>(nums[i], i));
    }

    return {};        
}

// 字母异位词分组
vector<vector<string>> groupAnagrams(vector<string>& strs) 
{
    unordered_map<string, vector<string>> umap;
    for (int i = 0; i < strs.size();i++) {
        string tempStr = strs[i];
        sort(tempStr.begin(),tempStr.end());
        umap[tempStr].emplace_back(strs[i]);
    }
    vector<vector<string>> rlt;
    for (auto iter = umap.begin(); iter != umap.end(); iter++) {
        rlt.emplace_back(iter->second);
    }

    return rlt;
}

// N叉树的层序遍历
vector<vector<int>> levelOrder(Node* root) 
{
    queue<Node*> myQ;
    vector<vector<int>> res;
    if(root != nullptr) myQ.push(root);
    while (!myQ.empty()) {
        int qz = myQ.size();
        vector<int> nodeList;
        for (int i = 0; i < qz; i++) {
            auto topNode = myQ.front();
            nodeList.emplace_back(topNode->val);
            myQ.pop();
            for (auto& child : topNode->children) {
                if (child != nullptr) {
                    myQ.push(child);
                }
            }
        }
        res.emplace_back(nodeList);
    }
    return res;      
}

// 二叉树的前序遍历
vector<int> preorderTraversal(TreeNode* root) 
{
    vector<int> res;
    if (root == nullptr) {
        return res;
    }
    stack<TreeNode *> mySt;
    mySt.emplace(root);
    while (!mySt.empty()) {
        TreeNode * topNode = mySt.top();
        res.emplace_back(topNode->val);
        mySt.pop();
        if (topNode->right) {
            mySt.emplace(topNode->right);
        }

        if(topNode->left) {
            mySt.emplace(topNode->left);
        }
    }
    return res;
}

// 二叉树的中序遍历
vector<int> inorderTraversal(TreeNode* root) 
{
    vector<int> res;
    stack<TreeNode *> mySt;
    TreeNode * curNode = root;
    while(curNode != nullptr || !mySt.empty()) {
        while(curNode != nullptr) {
            mySt.push(curNode);
            curNode = curNode->left;
        }

        TreeNode * topNode = mySt.top();
        mySt.pop();
        res.emplace_back(topNode->val);
        curNode = topNode->right;
    }
    return res;   
}