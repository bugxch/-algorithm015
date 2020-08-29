### 删除排序数组中的重复项

- 代码

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) 
    {
        if (nums.size() == 0) {
            return 0;
        }

        int left = 0;
        for (int right = 0; right < nums.size(); right++) {
            if (nums[left] == nums[right]) {
                // right++;
                continue;
            }
            left++;
            nums[left] = nums[right];
        }
        return left + 1;
    }
};
```

- 心得

  这道题目双指针法比较巧妙，使用两个指针，left指针指向下一个填充非重复元素的位置，right指针跳过重复元素，将每个非重复元素挑出来，赋值给left指针。因为仅仅一个for循环，所以复杂度为$O(n)$。

- 总结

  1. 需要考虑对特殊输入的处理，比如数组为空，字符串为空；
  2. 注意12行的注释掉的right++，这里刚开始是这一句的，但是在[1,2]用例中调试错误，我发现本意是自加1，但是for循环也会给right自加1，所以此处必须注释掉；
  3. right的计数从索引0开始，这里需要兼顾长度为1的数组

### 合并两个有序链表

- 代码

  ```c++
  class Solution {
  public:
      ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
          if (l1 == NULL) {
              return l2;
          }
          if (l2 == NULL) {
              return l1;
          }
          if (l1->val <= l2->val) {
              l1->next = mergeTwoLists(l1->next, l2);
              return l1;
          }
          l2->next = mergeTwoLists(l1, l2->next);
          return l2;
      }
  };
  ```

- 心得

  参考[为什么你学不会递归？告别递归，谈谈我的一些经验 - 帅地 - 博客园](https://www.cnblogs.com/kubidemanong/p/10538799.html)，和这道题比较相关的还有一道中等的题目[332. 重新安排行程 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reconstruct-itinerary/)，其中也用到了递归的技巧，我发现自己对递归的掌握很生疏，所以专门学习了递归的技巧。

  ### 两数之和

- 代码

  ```cpp
  class Solution {
  public:
      vector<int> twoSum(vector<int>& nums, int target) {
          unordered_map<int, int> lists;
          for (int i = 0; i < nums.size(); i++) {
              if(lists.find(target - nums[i]) != lists.end()) {
                  return vector<int>{lists[target - nums[i]], i};
              }
              lists.insert(pair<int, int>(nums[i], i));
          }
          return {};   
      }
  };
  ```

- 心得

  暴力解法是使用两重循环遍历所有的(i,j)序列对，然后检查是否两两的和为target。其实重新推演这个过程，如果抛开计算机，自己手动去解答这道题目，**人脑解决这个问题的逻辑**是，逐个考察当前元素，**查找当前元素之前已经遍历过的元素**，是否与当前元素的和满足条件。很明显，可以使用哈希结构将黑体部分的过程从$O(n)$降到$O(1)$，所以整个算法的复杂度也就降到了$O(n)$。仔细观察这个题目，有下面的两个预设条件：

  1. 整数数组的元素各不相同；
  2. 整个数组只对应1个答案

  哈希表的建立以`<num, index>`为pair建立，这样便于查找。

- 知识积累

  1. 对于查找某个序列中是否有某个值的问题，可以为序列建立哈希表，查询复杂度为$O(1)$；
  2. 凡事算法解题，可以想想如果是人脑解题，可以分解为哪些步骤，然后逐一审查这些步骤，是否可以通过数据结构或者其他的巧妙的解法将复杂度降低。通过局部优化，达到全局最优。

- 相关题目

  [面试题 01.01. 判定字符是否唯一 - 力扣（LeetCode）](https://leetcode-cn.com/problems/is-unique-lcci/)，如果去掉题目中不适用额外的数据结构的要求，也可以使用哈希的数据结构的$O(1)$的查询复杂度，因为人脑处理题目的逻辑是一样的，考察当前的元素，**查找当前元素之前已经遍历过的元素**，是否和当前元素重合，黑体字部分就可以使用哈希表。引申一下，也可以适用bitmap，bitmap也是一种特殊的哈希表。

### 接雨水

- 代码

  这道题我之前做过，使用双指针的方法，代码如下

  ```cpp
  class Solution {
  public:
      int trap(vector<int>& height) {
          int ans = 0;
          if (height.empty())
          {
              return ans;
          }
          int n = height.size();
          int left = 0, right = n - 1;
          int lmax = -1, rmax = -1;
          while (left < right)
          {
              lmax = max(height[left], lmax);
              rmax = max(height[right], rmax);
  
              if (lmax < rmax)
              {
                  ans += lmax - height[left];
                  left++;
              }
              else
              {
                  ans += rmax - height[right];
                  right--;
              }
          }
          return ans;
      }
  };
  ```


使用堆栈的方法的代码我后续补充，这个周末搬家，我周一或者其他时间再补充。