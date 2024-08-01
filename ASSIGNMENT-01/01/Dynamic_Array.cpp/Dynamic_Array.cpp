#include <iostream>
using namespace std ;
class DynamicArray {
private:
    int* array;
    size_t capacity;
    size_t size;
    double resizeFactor;

    void resize() {
        size_t newCapacity = static_cast<size_t>(capacity * resizeFactor);
        int* newArray = new int[newCapacity];

        for (size_t i = 0; i < size; i++) {
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

public:
    DynamicArray(size_t initialCapacity = 10, double resizeFactor = 1.5) 
        : capacity(initialCapacity), size(0), resizeFactor(resizeFactor) {
        array = new int[capacity];
    }

    ~DynamicArray() {
        delete[] array;
    }

    //Inserts an element at the specified index.

    void insertAt(size_t index, int value) {
        if (index > size) {
            std::cerr << "Index out of range\n";
            return;
        }
        if (size == capacity) resize();
        for (size_t i = size; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        size++;
    }

    // o Deletes the element at the specified index.

    void deleteAt(size_t index) {
        if (index >= size) {
            std::cerr << "Index out of range\n";
            return;
        }
        for (size_t i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
    }

    //  Returns the size of the dynamic array

    size_t getSize() const {
        return size;
    }

    //  Returns true if the dynamic array is empty, false otherwise

    bool isEmpty() const {
        return size == 0;
    }

    //  Rotates the dynamic array by k positions to the right.

    void rotateRight(size_t k) {
        if (size == 0) return;
        k = k % size;
        int* temp = new int[k];
        for (size_t i = 0; i < k; i++) {
            temp[i] = array[size - k + i];
        }
        for (size_t i = size - 1; i >= k; i--) {
            array[i] = array[i - k];
        }
        for (size_t i = 0; i < k; i++) {
            array[i] = temp[i];
        }
        delete[] temp;
    }

    //  Reverses the dynamic array.

    void reverse() {
        for (size_t i = 0; i < size / 2; i++) {
            int temp = array[i];
            array[i] = array[size - 1 - i];
            array[size - 1 - i] = temp;
        }
    }

    //  Appends an element to the end of the dynamic array.


    void append(int value) {
        if (size == capacity) resize();
        array[size++] = value;
    }

    //  Prepends an element to the beginning of the dynamic array.

    void prepend(int value) {
        insertAt(0, value);
    }

    // Merges two dynamic arrays into a single dynamic array.

    static DynamicArray merge(const DynamicArray& a, const DynamicArray& b) {
        DynamicArray result(a.size + b.size);
        for (size_t i = 0; i < a.size; i++) {
            result.append(a.array[i]);
        }
        for (size_t i = 0; i < b.size; i++) {
            result.append(b.array[i]);
        }
        return result;
    }
    // Interleaves two dynamic arrays into a single dynamic array.
    static DynamicArray interleave(const DynamicArray& a, const DynamicArray& b) {
        size_t newSize = a.size + b.size;
        DynamicArray result(newSize);
        size_t minSize = a.size < b.size ? a.size : b.size;
        size_t i = 0;
        for (; i < minSize; i++) {
            result.append(a.array[i]);
            result.append(b.array[i]);
        }
        for (; i < a.size; i++) {
            result.append(a.array[i]);
        }
        for (; i < b.size; i++) {
            result.append(b.array[i]);
        }
        return result;
    }

    // Returns the middle element of the dynamic array.

    int middleElement() const {
        if (size == 0) {
            std::cerr << "Array is empty\n";
            return -1;
        }
        return array[size / 2];
    }

    // Returns the index of the first occurrence of the specified element in the dynamic 
array, or -1 if the element is not found.

    int indexOf(int value) const {
        for (size_t i = 0; i < size; i++) {
            if (array[i] == value) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // Splits the dynamic array into two dynamic arrays at the specified index.

    void splitAt(size_t index, DynamicArray& first, DynamicArray& second) const {
        if (index > size) {
            std::cerr << "Index out of range\n";
            return;
        }
        first = DynamicArray(index);
        second = DynamicArray(size - index);
        for (size_t i = 0; i < index; i++) {
            first.append(array[i]);
        }
        for (size_t i = index; i < size; i++) {
            second.append(array[i]);
        }
    }



    void setResizeFactor(double factor) {
        if (factor <= 1.0) {
            std::cerr << "Resize factor must be greater than 1.0\n";
            return;
        }
        resizeFactor = factor;
    }
};

int main() {
    DynamicArray arr;

    arr.append(1);
    arr.append(2);
    arr.append(3);
    arr.prepend(0);

    cout << "Array after appending and prepending: ";
    for (size_t i = 0; i < arr.getSize(); i++) {
        cout << arr.middleElement() << " ";
    }
    cout << "\n";

    arr.insertAt(2, 10);
    cout << "Array after inserting 10 at index 2: ";
    for (size_t i = 0; i < arr.getSize(); i++) {
        cout << arr.middleElement() << " ";
    }
    cout << "\n";

    arr.deleteAt(2);
    cout << "Array after deleting element at index 2: ";
    for (size_t i = 0; i < arr.getSize(); i++) {
        cout << arr.middleElement() << " ";
    }
    cout << "\n";

    arr.rotateRight(2);
   cout << "Array after rotating right by 2: ";
    for (size_t i = 0; i < arr.getSize(); i++) {
        cout << arr.middleElement() << " ";
    }
    cout << "\n";

    arr.reverse();
    cout << "Array after reversing: ";
    for (size_t i = 0; i < arr.getSize(); i++) {
        cout << arr.middleElement() << " ";
    }
    cout << "\n";

    return 0;
}
