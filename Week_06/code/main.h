/*
 * @Author: your name
 * @Date: 2020-10-11 21:04:30
 * @LastEditTime: 2020-10-11 21:06:48
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \algorithm015\Week_06\code\main.h
 */
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <limits>
#include <stack>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <unordered_set>

 struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

 class Node {
 public:
     int val;
     Node* left;
     Node* right;
     Node* next;

     Node() : val(0), left(NULL), right(NULL), next(NULL) {}

     Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

     Node(int _val, Node* _left, Node* _right, Node* _next)
         : val(_val), left(_left), right(_right), next(_next) {}
 };

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

using namespace std;