class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int isAscend = 1;
        for (auto iter = digits.rbegin(); iter != digits.rend(); iter++) {
            *iter += isAscend;   
            isAscend = *iter / 10;
            *iter %= 10;
        }

        if (isAscend == 1) { // only possible for 1000000...0
            vector<int>rlt(digits.size() + 1, 0);
            rlt[0] = 1;  
            return rlt;
        }

        return digits;
    }
};