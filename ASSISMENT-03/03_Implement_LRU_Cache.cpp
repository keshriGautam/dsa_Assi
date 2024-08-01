#include<bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;  
    unordered_map<int, list<pair<int, int>>::iterator> map;  
    
    void moveToFront(int key, int value) {
        cache.erase(map[key]);
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
    
public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1;
        } else {
            int value = map[key]->second;
            moveToFront(key, value);
            return value;
        }
    }
    
    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            moveToFront(key, value);
        } else {
            if (cache.size() == capacity) {
                int lruKey = cache.back().first;
                cache.pop_back();
                map.erase(lruKey);
            }
            cache.push_front({key, value});
            map[key] = cache.begin();
        }
    }
};

int main() {
    LRUCache lruCache(2);
    
    lruCache.put(1, 1);
    lruCache.put(2, 2);
    cout << "Get 1: " << lruCache.get(1) << endl;   
    lruCache.put(3, 3);                           
    cout << "Get 2: " << lruCache.get(2) << endl;  
    lruCache.put(4, 4);                          
    cout << "Get 1: " << lruCache.get(1) << endl;  
    cout << "Get 3: " << lruCache.get(3) << endl;  
    cout << "Get 4: " << lruCache.get(4) << endl;  
    
    return 0;
}
