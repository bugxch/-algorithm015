class Solution {
public:
    void moveZeroes(vector<int>& nums) 
    {
        int left = 0;
        int len = nums.size();
        for (int right = 0; right < len; right++) {
            if (nums[right] != 0) {
                // swap left and right
                int temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
                left++;
            }
        }
    }
};