
### [53. 最大子序和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-subarray/)

我的代码如下所示

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};
```

题解的算法复杂度是$O(n)$。这道题比较巧妙的地方在如何定义状态一维变量`dp`，该题目比较巧妙得将**`dp[i]`定义为以元素`num[i]`结束（包括该元素）的子数组的最大和**，这样非常有利于递推关系的推导，具体可以参考我的[题解](https://leetcode-cn.com/problems/maximum-subarray/solution/rong-yi-li-jie-de-dong-tai-gui-hua-si-lu-by-bugxch/)。如果理解透彻之后，其实也可以将**`dp[i]`定义为以元素`num[i]`（包括该元素）开始的子数组的最大和**，所以会有下面的代码

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = nums[nums.size() -1];
        int maxVal = pre;
        for (int i = nums.size() - 2; i >= 0; i--) {
            pre = max(pre + nums[i], nums[i]);
            maxVal = max(maxVal, pre);
        }

        return maxVal;
    }
};
```

### [363. 矩形区域不超过 K 的最大数值和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/)

我的代码如下所示

```cpp
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) 
    {
        int row = matrix.size();

        if (row == 0) {
            return 0;
        }

        int maxArea = INT_MIN;
        int col = matrix[0].size();

        for (int left = 0; left < col; left++) {
            vector<int> colSum(row, 0);
            for (int right = left; right < col; right++) {
                for (int id = 0; id < row; id++) {
                    colSum[id] += matrix[id][right];
                }
                // find the nearest rectangle sum here
                maxArea = max(maxArea, GetmaxSum(colSum, k));
            }		
        }
        return maxArea;
    }
private:
    int GetmaxSum(vector<int>& colSum, const int k)
    {
        int colSize = colSum.size();
       
        vector<int> dp(colSum);

        int maxSum = dp[0];
        for (int i = 1; i < colSize; i++) {
            dp[i] = max(colSum[i], dp[i - 1] + colSum[i]);
            maxSum = max(maxSum, dp[i]);
        }
		// return maxsum if maxsum <= k
        if (maxSum <= k) {
            return maxSum;
        }
		// else 暴力解法
        maxSum = INT_MIN;
        for (int start = 0; start < colSize; start++) {
            int sum = 0;
            for (int end = start; end < colSize; end++) {
                sum += colSum[end];
                if (sum <= k) {
                    maxSum = max(maxSum, sum);
                }
            }
        }

        return maxSum;
    }
};
```

最坏情况下算法的复杂度是$O(n^4)$。这道题目是一个题中题，可以利用之前的[53. 最大子序和 ](https://leetcode-cn.com/problems/maximum-subarray/)和结果实现对于部分结果的提前预判。这道题目的关键是**如何遍历所有的子矩形既不遗漏重复又能形成递推关系**，参考如下示意图

![](https://pic.leetcode-cn.com/13fb1fcc1203665fe1c4ccc6221cef7e01921fe614b0e6b22a81a70eca4e79aa-image.png)

按照列的维度，逐列计算行元素的累积和，rowSum就代表了每个横向黄色的矩形的面积和，所以问题就转换成为如何计算rowSum中的最接近k的连续的子序列的和。