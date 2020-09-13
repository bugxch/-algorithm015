## 学习笔记

本周学习的是递归的概念。从我自己做题的体会，掌握递归的概念有两个关键点：

1. 理解计算机处理递归的运算逻辑；
2. 熟练掌握超哥总结的递归框架；

### 计算机处理递归的逻辑

计算机处理递归的方式，递归本质是程序自己调用自己，计算机处理函数调用会新开一个堆栈，将调用的参数写入堆栈之中，然后再调用函数逻辑进行计算，计算结束之后返回结果，销毁调用栈中的参数内容。就像超哥说的，这里的逻辑就像盗梦空间中的梦境一样，**一旦函数调用自己就会深入到新的一层梦境中**，周围的环境和人物都成新的，这刚好对应传入的参数都是新的，**函数调用结束之后会自动返回到上一层**，所以可以利用这个特性实现递归的功能。我个人对这个理解比较深刻的是[剑指 Offer 06. 从尾到头打印链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)，这道题目的解答是

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        if (head == nullptr) {
            return res;
        }
        res = reversePrint(head->next);
        res.push_back(head->val);
        return res;
    }
};
```

调用函数`reversePrint`自身，就是一层层下探到下一层梦境，直到到了链表的末尾停止，然后将这一层的val保存起来，之所以可以逆序将链表的元素打出来，就是因**为从梦境中一层层撤回到上一层**，所以又从链表的尾巴回溯到链表的开始第一个元素，**巧妙！！**

### 递归框架

递归框架是DFS和分治、回溯等常用递归算法的通用框架，非常有用，练习每道题，需要将这个框架烂熟于胸，先写框架再填充内容，基本上错的不会错太远，

```c++
void recursion(int level, int param) { 
  // recursion terminator
  if (level > MAX_LEVEL) { 
    // process result 
    return ; 
  }

  // process current logic 
  process(level, param);

  // drill down 
  recursion(level + 1, param);

  // reverse the current level status if needed
}
```

基本上上面的算法都可以归结到这个模板上来。