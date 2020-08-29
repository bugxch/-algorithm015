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
                continue;
            }
            left++;
            nums[left] = nums[right];
        }
        return left + 1;
    }
};