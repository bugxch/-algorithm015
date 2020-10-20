/*
 * @Author: bugxch
 * @Date: 2020-10-11 21:04:22
 * @LastEditTime: 2020-10-21 07:26:28
 * @LastEditors: Please set LastEditors
 * @Description: homework for algorithm train
 * @FilePath: \algorithm015\Week_06\code\main.cpp
 */
#include "main.h"

// 解数独

class Solution {
public:
   void solveSudoku(vector<vector<char>>& board)
    {
        bool rowT[9][9] = { false };
        bool colT[9][9] = { false };
        bool gridT[9][9] = { false };

        // scan sodu to make tables

        for (int i = 0; i < 9; i++)	{
            for (int j = 0;j < 9;j++) {
                auto ch = board[i][j];

                if (ch != '.') {
                    rowT[i][ch - '1'] = true;
                    colT[j][ch - '1'] = true;
                    gridT[i / 3 * 3 + j / 3][ch - '1'] = true;
                }
            }
        }

        if (backtraceSudo(board, 0, rowT, colT, gridT) == false) {
            cout << "There is no valid solution\n";
        }
    }
private:
    bool backtraceSudo(vector<vector<char>>& board, int idx, bool rowT[][9], bool colT[][9], bool gridT[][9])
    {
        if (idx == 81) {
            return true;
        }

        int x = idx / 9;
        int y = idx % 9;
        auto ch = board[x][y];

        if (ch >= '1' && ch <= '9') {
            return backtraceSudo(board, idx + 1, rowT, colT, gridT);
        }

        for (char next = '1'; next <= '9'; next++) {
            if (rowT[x][next - '1'] == true ||
                colT[y][next - '1'] == true ||
                gridT[x / 3 * 3 + y / 3][next - '1'] == true) {
                continue;
            }
            board[x][y] = next;
            rowT[x][next - '1'] = true;
            colT[y][next - '1'] = true;
            gridT[x / 3 * 3 + y / 3][next - '1'] = true;

            if (backtraceSudo(board, idx + 1, rowT, colT, gridT) == true) {
                return true;
            }

            rowT[x][next - '1'] = false;
            colT[y][next - '1'] = false;
            gridT[x / 3 * 3 + y / 3][next - '1'] = false;
            board[x][y] = '.';
        }

        return false;
    }
};

// 实现前缀树
class Trie {
public:
	Trie()
	{
		IsEnd = false;
		memset(next, 0, sizeof(next));
	}

	void insert(string word)
	{
		Trie* node = this;
		for (auto& ch : word) {
			if (node->next[ch - 'a'] == nullptr) {
				node->next[ch - 'a'] = new Trie();
			}
			node = node->next[ch - 'a'];
		}

		node->IsEnd = true;
	}

	bool search(string word)
	{
		Trie* node = this;
		for (auto& ch : word) {
			if (node->next[ch - 'a'] == nullptr) {
				return false;
			}

			node = node->next[ch - 'a'];
		}

		return node->IsEnd;
	}

	bool startsWith(string prefix)
	{
		Trie* node = this;
		for (auto& ch : prefix) {
			if (node->next[ch - 'a'] == nullptr) {
				return false;
			}

			node = node->next[ch - 'a'];
		}

		return true;
	}

private:
	bool IsEnd;
	Trie* next[26];
};

// 朋友圈
class Uf {
public:
	Uf(int n)
	{
		for (int i = 0; i < n; ++i) {
			m_pre.emplace_back(i);
		}
		m_count = n;
	}

	~Uf( )
	{
		m_count = 0;
		m_pre.clear();
	}

	int GetFather(const int a) {
		int r = a;
		while (m_pre[r] != r) {
			r = m_pre[r];
		}

		// supress the route if father has found
		int i = a;
		int j;
		while (i != r) {
			j = m_pre[i];
			m_pre[i] = r;
			i = j;
		}
		return r;
	}

	int GetSize() const {
		return m_count;
	}

	void UninSet(int a, int b) {
		int af = GetFather(a);
		int bf = GetFather(b);

		if (af == bf) {
			return;
		}

        if (bf < af) {
            swap(bf, af);
        }

		m_pre[bf] = af;
		--m_count;
	}
private:
	vector<int> m_pre;
	int m_count;
};


class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        Uf myuf(M.size());
        for (int i = 0; i < M.size(); ++i) {
            for (int j = i + 1; j < M.size(); ++j) {
                if (M[i][j] == 1) {
                    myuf.UninSet(i, j);
                }
            }
        }

        return myuf.GetSize();
    }
};

// 被围绕的区域
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

class Solution {
public:
    void solve(vector<vector<char>>& board)
    {
        int row = board.size();
        if (row == 0) {
            return;
        }
        int col = board[0].size();

        vector<vector<int>> dirs = {
            {0, 1},
            {0, -1},
            {-1, 0},
            {1, 0}
        };

        Uf myf(board);

        set<int> edgeNode;

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (board[i][j] == 'X') continue;
                //board[i][j] = 'X';
                if (i == 0 || i == row - 1 || j == 0 || j == col - 1) {
                    edgeNode.insert(myf.search(i * col + j));
                }
                // check neighbor
                for (auto& dir : dirs) {
                    int nr = i + dir[0];
                    int nc = j + dir[1];
                    if (nr < 0 || nr >= row || nc < 0 ||
                        nc >= col || board[nr][nc] == 'X') {
                        continue;
                    }
                    myf.unionf(i * col + j, nr * col + nc);

                    if ( nr == 0 ||nr == row - 1 || nc == 0 || nc == col - 1) {
                        edgeNode.insert(myf.search(i * col + j));
                    }
                }
            }
        }

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int parent = myf.search(i * col + j);
                if (parent != -1 && edgeNode.count(parent) == 0) {
                    board[i][j] = 'X';
                }
            }
        }
    }
};