#include<bits/stdc++.h>
using namespace std;

class RandomizedSet {
private:
    vector<int> nums;
    unordered_map<int, int> numToIndex;

public:
    RandomizedSet() {
    }
    
    bool insert(int val) {
        if (numToIndex.find(val) != numToIndex.end()) {
            return false;  
        }
        nums.push_back(val);
        numToIndex[val] = nums.size() - 1;
        return true;
    }
    
    bool remove(int val) {
        if (numToIndex.find(val) == numToIndex.end()) {
            return false;  
        }
        int lastElement = nums.back();
        int idx = numToIndex[val];
        nums[idx] = lastElement;
        numToIndex[lastElement] = idx;
        nums.pop_back();
        numToIndex.erase(val);
        return true;
    }
    
    int getRandom() {
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }
};
