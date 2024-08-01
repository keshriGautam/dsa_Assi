#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    size_t listSize;

public:
    SinglyLinkedList() : head(nullptr), listSize(0) {}

    ~SinglyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void insertAt(size_t index, int value) {
        if (index > listSize) {
            std::cerr << "Index out of range\n";
            return;
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* prev = nullptr;
            Node* curr = head;
            for (size_t i = 0; i < index; ++i) {
                prev = curr;
                curr = curr->next;
            }
            newNode->next = curr;
            prev->next = newNode;
        }
        listSize++;
    }

    void deleteAt(size_t index) {
        if (index >= listSize) {
            std::cerr << "Index out of range\n";
            return;
        }
        Node* temp = head;
        if (index == 0) {
            head = head->next;
        } else {
            Node* prev = nullptr;
            for (size_t i = 0; i < index; ++i) {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
        }
        delete temp;
        listSize--;
    }

    size_t getSize() const {
        return listSize;
    }

    bool isEmpty() const {
        return listSize == 0;
    }

    void rotateRight(size_t k) {
        if (listSize == 0) return;
        k = k % listSize;
        if (k == 0) return;

        Node* oldTail = head;
        Node* newTail = head;
        Node* newHead = head;

        for (size_t i = 0; i < listSize - 1; ++i) {
            oldTail = oldTail->next;
        }
        for (size_t i = 0; i < listSize - k - 1; ++i) {
            newTail = newTail->next;
        }
        newHead = newTail->next;

        oldTail->next = head;
        newTail->next = nullptr;
        head = newHead;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        listSize++;
    }

    void prepend(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    static SinglyLinkedList merge(const SinglyLinkedList& a, const SinglyLinkedList& b) {
        SinglyLinkedList result;
        Node* temp = a.head;
        while (temp != nullptr) {
            result.append(temp->data);
            temp = temp->next;
        }
        temp = b.head;
        while (temp != nullptr) {
            result.append(temp->data);
            temp = temp->next;
        }
        return result;
    }

    static SinglyLinkedList interleave(const SinglyLinkedList& a, const SinglyLinkedList& b) {
        SinglyLinkedList result;
        Node* tempA = a.head;
        Node* tempB = b.head;
        while (tempA != nullptr || tempB != nullptr) {
            if (tempA != nullptr) {
                result.append(tempA->data);
                tempA = tempA->next;
            }
            if (tempB != nullptr) {
                result.append(tempB->data);
                tempB = tempB->next;
            }
        }
        return result;
    }

    int middleElement() const {
        if (listSize == 0) {
            std::cerr << "List is empty\n";
            return -1;
        }
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->data;
    }

    int indexOf(int value) const {
        Node* temp = head;
        for (size_t i = 0; i < listSize; i++) {
            if (temp->data == value) {
                return static_cast<int>(i);
            }
            temp = temp->next;
        }
        return -1;
    }

    void splitAt(size_t index, SinglyLinkedList& first, SinglyLinkedList& second) const {
        if (index > listSize) {
            std::cerr << "Index out of range\n";
            return;
        }
        first = SinglyLinkedList();
        second = SinglyLinkedList();
        Node* temp = head;
        for (size_t i = 0; i < index; ++i) {
            first.append(temp->data);
            temp = temp->next;
        }
        while (temp != nullptr) {
            second.append(temp->data);
            temp = temp->next;
        }
    }

    void print() const {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "null\n";
    }
};

int main() {
    SinglyLinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.prepend(0);
    list.print();

    list.insertAt(2, 10);
    cout << "After inserting 10 at index 2: ";
    list.print();

    list.deleteAt(2);
    cout << "After deleting element at index 2: ";
    list.print();

    list.rotateRight(2);
    cout << "After rotating right by 2: ";
    list.print();

    list.reverse();
    cout << "After reversing: ";
    list.print();

    SinglyLinkedList list1;
    list1.append(1);
    list1.append(3);
    list1.append(5);

    SinglyLinkedList list2;
    list2.append(2);
    list2.append(4);
    list2.append(6);

    SinglyLinkedList mergedList = SinglyLinkedList::merge(list1, list2);
    cout << "Merged list: ";
    mergedList.print();

    SinglyLinkedList interleavedList = SinglyLinkedList::interleave(list1, list2);
    cout << "Interleaved list: ";
    interleavedList.print();

    cout << "Middle element of the list: " << list.middleElement() << "\n";

    cout << "Index of element 3: " << list.indexOf(3) << "\n";

    SinglyLinkedList firstHalf, secondHalf;
    list.splitAt(2, firstHalf, secondHalf);
    cout << "First half: ";
    firstHalf.print();
    cout << "Second half: ";
    secondHalf.print();

    return 0;
}
