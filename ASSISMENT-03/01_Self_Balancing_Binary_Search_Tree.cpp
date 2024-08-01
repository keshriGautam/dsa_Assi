#include <iostream>
using namespace std;

struct AVLNode {
    int key, height, size;
    AVLNode *left, *right;
    
    AVLNode(int k) : key(k), height(1), size(1), left(NULL), right(NULL) {}
};

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int size(AVLNode* node) {
    return node ? node->size : 0;
}

int balanceFactor(AVLNode* node) {
    return height(node->left) - height(node->right);
}

void updateHeightAndSize(AVLNode* node) {
    if (node) {
        node->height = 1 + max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right);
    }
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    updateHeightAndSize(y);
    updateHeightAndSize(x);
    
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    updateHeightAndSize(x);
    updateHeightAndSize(y);
    
    return y;
}

AVLNode* balance(AVLNode* node) {
    updateHeightAndSize(node);
    
    if (balanceFactor(node) > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    if (balanceFactor(node) < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

AVLNode* insert(AVLNode* node, int key) {
    if (!node) return new AVLNode(key);
    
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    
    return balance(node);
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVLNode* remove(AVLNode* node, int key) {
    if (!node) return node;
    
    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = NULL;
            } else
                *node = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }
    
    if (!node) return node;
    
    return balance(node);
}

bool find(AVLNode* node, int key) {
    if (!node) return false;
    if (key == node->key) return true;
    if (key < node->key) return find(node->left, key);
    return find(node->right, key);
}

int order_of_key(AVLNode* node, int key) {
    if (!node) return 0;
    if (key < node->key)
        return order_of_key(node->left, key);
    else if (key > node->key)
        return size(node->left) + 1 + order_of_key(node->right, key);
    else
        return size(node->left);
}

int get_by_order(AVLNode* node, int k) {
    if (!node) return -1;
    int leftSize = size(node->left);
    if (k < leftSize)
        return get_by_order(node->left, k);
    else if (k > leftSize)
        return get_by_order(node->right, k - leftSize - 1);
    return node->key;
}

int main() {
    AVLNode* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);
    
    cout << "Find 15: " << find(root, 15) << endl;
    cout << "Find 40: " << find(root, 40) << endl;
    cout << "Order of key 25: " << order_of_key(root, 25) << endl;
    cout << "Element at order 3: " << get_by_order(root, 3) << endl;
    
    root = remove(root, 20);
    cout << "Find 20: " << find(root, 20) << endl;
    cout << "Order of key 25: " << order_of_key(root, 25) << endl;
    cout << "Element at order 3: " << get_by_order(root, 3) << endl;
    
    return 0;
}
