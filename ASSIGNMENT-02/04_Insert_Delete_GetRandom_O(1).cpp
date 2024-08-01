#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
using namespace std;

class RandomizedCollection {
private:
    vector<int> nums;
    unordered_map<int, unordered_set<int>> numToIndices;

public:
    RandomizedCollection() {
    }
    
    bool insert(int val) {
        nums.push_back(val);
        numToIndices[val].insert(nums.size() - 1);
        return numToIndices[val].size() == 1;
    }
    
    bool remove(int val) {
        if (numToIndices.find(val) == numToIndices.end() || numToIndices[val].empty()) {
            return false;
        }
        int removeIdx = *numToIndices[val].begin();
        int lastElement = nums.back();
        nums[removeIdx] = lastElement;
        numToIndices[val].erase(removeIdx);
        if (removeIdx != nums.size() - 1) {
            numToIndices[lastElement].erase(nums.size() - 1);
            numToIndices[lastElement].insert(removeIdx);
        }
        nums.pop_back();
        if (numToIndices[val].empty()) {
            numToIndices.erase(val);
        }
        return true;
    }
    
    int getRandom() {
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }
};
