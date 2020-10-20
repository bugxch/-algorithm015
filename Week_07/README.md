### [64. 最小路径和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-path-sum/)

#### 代码

我提交的代码

```cpp
int minPathSum(vector<vector<int>>& grid)
 {
    int row = grid.size();
    int col = grid[0].size();

    for (int i = 1; i < row; i++) {
        grid[i][0] = grid[i - 1][0] + grid[i][0];
    }

    for (int i = 1; i < col; i++) {
        grid[0][i] = grid[0][i - 1] + grid[0][i];
    }

    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j];
        }
    }

    return grid[row -1][col-1];
}
```

这个题目比较简单，因为对于任意的位置，它的最短路径是上面和左面的位置的最小值加１，递推公式一目了然。

### [221. 最大正方形 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximal-square/)

我的代码

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int row = matrix.size();
        if (row == 0) {
            return 0;
        }
        int col = matrix[0].size();

        vector<vector<int>> dp(row, vector<int>(col));
        int maxArea = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = matrix[i][j] - '0';
                }
                else if(matrix[i][j] == '0'){
                    dp[i][j] = 0;
                }
                else {
                    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                }
                maxArea = max(dp[i][j], maxArea);
            }
        }

        return maxArea * maxArea;
        }
};
```

这道题目的递推公式比较难理解，上面的代码中`dp[i][j]`表示以位置(i,j)为右下角的最大正方形的边长，这个题目的解题思路与最大子序列和有点类似，都是以某个点为已知序列或者正方形，可以参考我之前写的[容易理解的动态规划思路 - 最大子序和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-subarray/solution/rong-yi-li-jie-de-dong-tai-gui-hua-si-lu-by-bugxch/)。	

### [91. 解码方法 - 力扣（LeetCode）](https://leetcode-cn.com/problems/decode-ways/submissions/)

我的代码

```cpp
class Solution {
public:
    int numDecodings(string s) {
        if (s.size() == 0 || s[0] == '0') {
            return 0;
        }

        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int j = 1; j < s.size(); j++) {
            if (!isValidStr(s.substr(j, 1)) && !isValidStr(s.substr(j - 1, 2))) {
                return 0;
            }

            if (isValidStr(s.substr(j, 1))) {
                dp[j + 1] += dp[j];
            }

            if (isValidStr(s.substr(j - 1, 2))) {
                dp[j + 1] += dp[j - 1];
            }
        }

        return dp[s.size()];
    }
private:
    bool isValidStr(string s) 
    {
        if (s.size() > 2 || s[0] == '0') {
            return false;
        }

        if (s.size() == 2 && stoi(s) > 26) {      
            return false;    
        }

        return true;
    }
};
```

这道题想得比较久，最后还是自己做出来了，参考我写的[C++动态规划 - 解码方法 - 力扣（LeetCode）](https://leetcode-cn.com/problems/decode-ways/solution/cdong-tai-gui-hua-by-bugxch/)。

### [416. 分割等和子集 - 力扣（LeetCode）](https://leetcode-cn.com/problems/partition-equal-subset-sum/)

这是今天的leetcode的题目，我的代码如下

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto num : nums) {
            sum += num;
        }

        if (nums.size() < 2 || (sum & 0x01) == 1) {
            return false;
        }

        int target = sum / 2;

        vector<bool> preVec(target + 1, false);
        vector<bool> curVec(preVec);

        // init the matrix
        if (nums[0] <= target) {
            preVec[nums[0]] = true;
        }

        preVec[0] = true;
        curVec[0] = true;

        for (int i = 1; i < nums.size(); i++) {
            for (int j = 1; j < target + 1; j++) {
                if (nums[i] > j) {
                    curVec[j] = preVec[j];
                    continue;
                }
                curVec[j] = preVec[j] || preVec[j - nums[i]];
            }		
            preVec = curVec;
        }

        return curVec[target];
    }
};
```

这道题目实际上和0-1背包问题是相似的，只是问题变为在n个物品中挑选若干个物品，使得物品的价格总和是已知总和的一半，参考我今年年初写的[01背包问题详解 - Dive Into Think](https://bugxch.github.io/post/01%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E8%AF%A6%E8%A7%A3/)。

---

最大心得，就是**多练习，多想，**动态规划的题目不会做就真不会，cover足够多的题目才能游刃有余。