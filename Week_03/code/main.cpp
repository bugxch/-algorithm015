// 组合，No. 77
void dfsCombine(vector<int>& curPath, vector<vector<int>>& res, const int n, const int k)
{
    if (curPath.size() == k) {
        res.emplace_back(curPath);
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (curPath.empty() || i > curPath.back()) {
            curPath.emplace_back(i);
            dfsCombine(curPath, res, n, k);
            curPath.pop_back();
        }
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    if (k > n || k <= 0) return res;
    vector<int> curPath;
    dfsCombine(curPath, res, n, k);
    return res;
}

// No. 46 全排列
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {       
        vector<bool> used(nums.size(), false);
        dfsPermute(nums, used);
        return res;        
    }
private:
    vector<vector<int>> res;
    vector<int> curPath;
    void dfsPermute(vector<int>& nums, vector<bool>& used)
    {
        if (curPath.size() == nums.size()) {
            res.emplace_back(curPath);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) {
                continue;
            }
            curPath.emplace_back(nums[i]);
            used[i] = true;
            dfsPermute(nums, used);
            used[i] = false;
            curPath.pop_back();
        }
    }
};

// No. 47 全排列II
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> curPath;
        vector<bool> used(nums.size(), false);
        dfsPermute(nums, used, curPath, res);
        return res;     
    }
private:
    void dfsPermute(vector<int>& nums, vector<bool>& used, vector<int>&curPath, vector<vector<int>> & res)
    {
       if (curPath.size() == nums.size()) {
            res.emplace_back(curPath);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) {
                continue;
            }

            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
                continue;
            }

            curPath.emplace_back(nums[i]);
            used[i] = true; 
            dfsPermute(nums, used, curPath, res);
            used[i] = false;    
            curPath.pop_back();
        }
    }
};

//No. 17 电话号码字母组合

class Solution {
public:    
    vector<string> letterCombinations(string digits) {
        vector<string> rlt;
        const int depth = digits.size();
        if (depth == 0) {
            return rlt;
        }

        vector<int> digitsList;
        for (int i = 0; i < depth; i++) {
            digitsList.push_back(digits[i] - '0');
        }

        string curPath;
        dfsPhone(digitsList, 0, depth, curPath, rlt);
        return rlt;
        
    }
private:
    const vector<string> phoneNum = { "0000", "xxx$$","abc", "def" , "ghi", "jkl","mno","pqrs", "tuv", "wxyz" };
    void dfsPhone(const vector<int>& digitsList, int depth, const int maxDepth, string curPath, vector<string>& rlt)
    {
        if (depth == maxDepth) {
            rlt.push_back(curPath);
            return;
        }

        int sz = phoneNum[digitsList[depth]].size();
        for (int i = 0; i < sz; i++) {
            string nextPath = curPath + phoneNum[digitsList[depth]][i];
            dfsPhone(digitsList, depth + 1, maxDepth, nextPath, rlt);
        }
        return;
    }
};