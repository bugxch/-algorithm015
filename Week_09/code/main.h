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

using namespace std;

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

class Uf {
public:
    Uf(vector<vector<char>> & borad)
    {
        count = 0;
        int nr = borad.size();
        int nc = borad[0].size();
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                if (borad[i][j] == 'O') {
                    pre.emplace_back(i * nc + j);
                    ++count;
                } else {
                    pre.emplace_back(-1);
                }
            }
        }
    }

    int search(int a) {
        int r = a;
        while (pre[r] != r) {
            r = pre[r];
            if (r == -1) {
                return -1;
            }
        }

        int j;
        int x = a;
        while (x != r) {
            j = pre[x];
            pre[x] = r;
            x = j;
        }

        return r;
    }

    int getsize() const {
        return count;
    }

    void unionf(int a, int b) {
        int af = search(a);
        int bf = search(b);

        if (af == bf) {
            return;
        }

        if (bf < af) {
            swap(bf, af);
        }

        pre[bf] = af;
        --count;
    }

private:
    vector<int> pre;
    int count;
};