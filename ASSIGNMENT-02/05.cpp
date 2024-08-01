class ListNode {
public:
    int val;
    ListNode* next;

    ListNode(int value) : val(value), next(nullptr) {}
};

class MyLinkedList {
private:
    ListNode* head;
    int size;

public:
    MyLinkedList() {
        head = nullptr;
        size = 0;
    }
    
    int get(int index) {
        if (index < 0 || index >= size) {
            return -1; // Invalid index
        }
        ListNode* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->val;
    }
    
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    void addAtTail(int val) {
        ListNode* newNode = new ListNode(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            ListNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return; // Invalid index
        }
        if (index == 0) {
            addAtHead(val);
        } else {
            ListNode* newNode = new ListNode(val);
            ListNode* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            size++;
        }
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return; // Invalid index
        }
        if (index == 0) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        } else {
            ListNode* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            ListNode* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        size--;
    }
    
    ~MyLinkedList() {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
