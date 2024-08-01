#include<bits/stdc++.h>
using namespace std;

enum ProbingMethod {
    LINEAR,
    QUADRATIC
};

class HashMap {
private:
    vector<pair<int, int>> table;
    vector<bool> occupied;
    int size;
    int capacity;
    ProbingMethod probingMethod;

    int hash(int key) {
        return key % capacity;
    }

    int probe(int idx, int i) {
        if (probingMethod == LINEAR) {
            return (idx + i) % capacity;
        } else { // QUADRATIC
            return (idx + i * i) % capacity;
        }
    }

public:
    HashMap(int cap, ProbingMethod method) : capacity(cap), size(0), probingMethod(method) {
        table.resize(capacity, {-1, -1});
        occupied.resize(capacity, false);
    }

    bool find(int key) {
        int idx = hash(key);
        int i = 0;
        while (occupied[probe(idx, i)] && table[probe(idx, i)].first != key) {
            i++;
            if (i == capacity) return false; // All slots checked
        }
        return occupied[probe(idx, i)] && table[probe(idx, i)].first == key;
    }

    void insert(int key, int value) {
        if (size == capacity) return; // HashMap is full

        int idx = hash(key);
        int i = 0;
        while (occupied[probe(idx, i)] && table[probe(idx, i)].first != key) {
            i++;
        }

        int insertIdx = probe(idx, i);
        table[insertIdx] = {key, value};
        if (!occupied[insertIdx]) {
            occupied[insertIdx] = true;
            size++;
        }
    }

    void remove(int key) {
        int idx = hash(key);
        int i = 0;
        while (occupied[probe(idx, i)] && table[probe(idx, i)].first != key) {
            i++;
            if (i == capacity) return; // All slots checked
        }

        int removeIdx = probe(idx, i);
        if (occupied[removeIdx] && table[removeIdx].first == key) {
            occupied[removeIdx] = false;
            size--;
        }
    }
};

int main() {
    // Testing with Linear Probing
    cout << "Testing Linear Probing:" << endl;
    HashMap hmlp(7, LINEAR);
    hmlp.insert(1, 100);
    hmlp.insert(2, 200);
    hmlp.insert(8, 300);

    cout << "Find 1: " << hmlp.find(1) << endl;  // Output: 1
    cout << "Find 3: " << hmlp.find(3) << endl;  // Output: 0

    hmlp.remove(1);
    cout << "Find 1: " << hmlp.find(1) << endl;  // Output: 0

    // Testing with Quadratic Probing
    cout << "\nTesting Quadratic Probing:" << endl;
    HashMap hmq(7, QUADRATIC);
    hmq.insert(1, 100);
    hmq.insert(2, 200);
    hmq.insert(8, 300);

    cout << "Find 1: " << hmq.find(1) << endl;  // Output: 1
    cout << "Find 3: " << hmq.find(3) << endl;  // Output: 0

    hmq.remove(1);
    cout << "Find 1: " << hmq.find(1) << endl;  // Output: 0

    return 0;
}
