#include "main.h"

// 91. 解码方法
static bool isValidStr(string s)
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

// 5. 最长回文子串
 string longestPalindrome(string s) {
    int len = s.size();
    vector<vector<bool>> dp(len, vector<bool>(len, false));
    int maxLen = 0;
    if (len > 0) {
        maxLen = 1;
    }
    int startId = 0;

    // base case string
    for (int i = 0; i < len; i++) {
        dp[i][i] = true;
        if (i < len - 1) {
            dp[i][i + 1] = (s[i] == s[i + 1]);
            if (dp[i][i + 1] && maxLen < 2) {
                maxLen = 2;
                startId = i;
            }
        }
    }

    for (int i = len - 3; i >= 0; i--) {
        for (int j = i + 2; j < len; j++) {
            dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
            if (dp[i][j] && (j - i + 1) > maxLen) {
                maxLen = j - i + 1;
                startId = i;
            }
        }
    }

    return s.substr(startId, maxLen);
}

// 438. 找出所有字母异位词
 vector<int> findAnagrams(string s, string p) {
    // 用数组记录答案，效率比vector更高
    vector<int> res;
    int left = 0, right = 0;
    unordered_map<char, int> needs;
    unordered_map<char, int> window;
    for (char c : p) needs[c]++;
    int match = 0;

    while (right < s.size()) {
        char c1 = s[right];
        if (needs.count(c1)) {
            window[c1]++;
            if (window[c1] == needs[c1])
                match++;
        }
        right++;

        while (match == needs.size()) {
            // 如果 window 的大小合适
            // 就把起始索引 left 加入结果
            if (right - left == p.size()) {
                res.push_back(left);
            }
            char c2 = s[left];
            if (needs.count(c2)) {
                window[c2]--;
                if (window[c2] < needs[c2])
                    match--;
            }
            left++;
        }
    }
    return res;
}

// 387. 字符串中的第一个唯一字符
int firstUniqChar(string s) {
    unordered_map<char, int> umap;

    for (auto & ch : s) {
        umap[ch]++;
    }

    for (int i = 0;i < s.size();i++) {
        if (umap.count(s[i]) && umap[s[i]] > 1) {
            continue;
        }
        return i;
    }

    return -1;
}
