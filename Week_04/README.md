### [860. 柠檬水找零 - 力扣（LeetCode）](https://leetcode-cn.com/problems/lemonade-change/)

#### 代码

我提交的代码

```cpp
bool lemonadeChange(vector<int>& bills) 
{        
    map<int, int, greater<int>> umap;
    int curSum = 0;
    for (auto bill : bills) {
        int res = bill - 5;
        if (res > 0) {
            for (auto iter = umap.begin(); iter != umap.end(); iter++) {
                while (res > 0 && res >= iter->first && iter->second > 0) {
                    res -= iter->first;
                    iter->second--;
                }
            }
            if (res != 0) {
                return false;
            }
        }
        umap[bill]++;
        curSum += 5;
    }
    return true;      
}
```

我的代码比较复杂，通用性更强一些，基本的思路是使用map保存每一次找零之后的零钱的分布（比如当前有2张5元，2张10元硬币），每次找零如果大于0，那么就从最大的数开始找，直到找零的结果为0为止，如果最后的结果大于0，那么就认为找零找不出来，我的时间复杂度是$O(n^2)$，空间复杂度是$O(n)$。其实看了[官方题解](https://leetcode-cn.com/problems/lemonade-change/solution/ning-meng-shui-zhao-ling-by-leetcode/)，这道题的找零的数目不是5就是15，找零的方式也很有限，其实可以按照这个解法的复杂度更小，速度更快。

```java
 public boolean lemonadeChange(int[] bills) 
 {
     int five = 0, ten = 0;
     for (int bill: bills) {
         if (bill == 5)
             five++;
         else if (bill == 10) {
             if (five == 0) return false;
             five--;
             ten++;
         } else {
             if (five > 0 && ten > 0) {
                 five--;
                 ten--;
             } else if (five >= 3) {
                 five -= 3;
             } else {
                 return false;
             }
         }
     }

     return true;
 }
```

### [122. 买卖股票的最佳时机 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

我的代码

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;        
    }
};
```

从上帝视角看股票风云沉浮，只要有利可图就**低买高卖**，是为**贪心**。

### [455. 分发饼干 - 力扣（LeetCode）](https://leetcode-cn.com/problems/assign-cookies/description/)

我的代码

```cpp
int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int child = 0;
        int cookie = 0;
        while (child < g.size() && cookie < s.size()) {
            if (s[cookie] >= g[child]) {
                child++;            
            }
            cookie++;
        }
        return child;
    }
```

思路比较简单，孩子的胃口和饼干都按照从小到大排序，使用两个指针分别指向第一个元素，如果当前的饼干可以满足当前小孩的胃口，那么喂饱一个小孩，否则饼干加1（寻找更大的饼干满足当前小孩的胃口），直到两个指针的某一个达到边界为止。

### [874. 模拟行走机器人 - 力扣（LeetCode）](https://leetcode-cn.com/problems/walking-robot-simulation/description/)

我的代码如下

```cpp
int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) 
{
    pair<int, int> pos(0, 0);
    int maxDistance = 0;
    int curDir = 1;

    set<pair<int, int>> obstacleSet;
    for (auto obstacle : obstacles) {
        obstacleSet.emplace(obstacle[0], obstacle[1]);
    }
    
    const vector<pair<int, int>> dir{
        {-1, 0}, // 左
        {0, 1},  // 上
        {1, 0},  // 右
        {0, -1}  // 下
    };

    for (auto command : commands) {
        if (command == -2) {
            curDir = (curDir - 1) % 4;
        }
        else if (command == -1) {
            curDir = (curDir + 1) % 4;
        }
        else {
            for (int j = 0; j < command; j++) {			
				int x = pos.first + dir[curDir].first;
				int y = pos.second + dir[curDir].second;
                
                // obstacles crossed
                if (obstacleSet.find(make_pair(x, y)) != obstacleSet.end()) {
                    break;
                }
                pos.first = x;
                pos.second = y;
                maxDistance = max(maxDistance, x * x + y * y);				
            }           
        }
        while (curDir < 0) { curDir += 4; }
    }
    return maxDistance;
}
```

算法时间复杂度是$O(n^2)$，两层循环。说实话，这道题没有看出来和贪心有什么关系，估计是求当前最短距离的时候需要将每一步的距离和当前最大距离做比较吧。这里还有个小trick，第40行的代码，`while (curDir < 0) { curDir += 4; }`，C++中的`%`运算，如果`-1 % 4 = -1`，而不是3，所以需要根据需要补齐到非负整数，这样才能作为dir的index的值。

### [127. 单词接龙 - 力扣（LeetCode）](https://leetcode-cn.com/problems/word-ladder/submissions/)

```cpp
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        
        queue<string> myQ;
        unordered_map<string, bool> umap;
        for (auto & str : wordList) {
            umap[str] = false;
        }

        myQ.push(beginWord);
        umap[beginWord] = true;
        int depth = 1;
        while (!myQ.empty()) {
            int qz = myQ.size();
            for (int i = 0; i < qz; i++) {
                string topStr = myQ.front();
                myQ.pop();

                if (topStr == endWord) {
                    return depth;
                }

                for (int j = 0; j < topStr.length(); j++) {
                    string tempStr = topStr;
                    for (int k = 0; k < 26; k++) {
                        tempStr[j] = 'a' + k; 
                        if (umap.count(tempStr) > 0 && umap[tempStr] == false) {
                            myQ.push(tempStr);
                            umap[tempStr] = true;
                        }
                    }
                }
            }
            depth++;
        }
        return 0;        
    }
```

这道题的核心算法就是BFS，涉及到深度的都可以用BFS搞定，需要注意的是使用umap的哈希结构保存访问过的节点，这样就可以实现剪枝，快速找到问题的答案。