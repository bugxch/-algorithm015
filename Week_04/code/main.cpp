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