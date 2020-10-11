/*
 * @Author: bugxch
 * @Date: 2020-10-11 21:04:22
 * @LastEditTime: 2020-10-11 21:16:52
 * @LastEditors: Please set LastEditors
 * @Description: homework for algorithm train
 * @FilePath: \algorithm015\Week_06\code\main.cpp
 */
#include "main.h"

// 最小路径和
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

// 解码方法

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

int numDecodings(string s)
{
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

// 最大正方形
int maximalSquare(vector<vector<char>>& matrix)
{
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