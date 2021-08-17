/*The structure of the class is
class MinHeap
{
    int *harr;
    int capacity;
    int heap_size;

public:
MinHeap(int cap=100) {heap_size = 0; capacity = cap; harr = new int[cap];}

    int extractMin();
    void deleteKey(int i);
    void insertKey(int k);
};*/

namespace {
    constexpr int leftChildIndexOf(const int index)
    {
        return index * 2 + 1;
    }
    
    constexpr int rightChildIndexOf(const int index)
    {
        return index * 2 + 2;
    }
    
    constexpr int parentIndexOf(const int index)
    {
        return (index - 1) / 2;
    }
}

/* Removes min element from min heap and returns it */
int MinHeap::extractMin()
{
    if (heap_size == 0) return -1;
    
    const auto ret = harr[0];
    deleteKey(0);
    return ret;
}

/* Removes element from position x in the min heap  */
void MinHeap::deleteKey(int i)
{
    if (heap_size <= i || --heap_size == i) return;
    harr[i] = harr[heap_size];
    
    // heapify down
    for (; ; ) {
        const auto left = leftChildIndexOf(i);
        if (left >= heap_size) break;
        
        const auto right = rightChildIndexOf(i);
        const auto child = (right < heap_size && harr[right] < harr[left]
                                ? right
                                : left);
        if (harr[i] <= harr[child]) break;
        
        swap(harr[i], harr[child]);
        i = child;
    }
}

/* Inserts an element at position x [???] into the min heap*/
void MinHeap::insertKey(const int k)
{
    if (heap_size == capacity) return;
    
    harr[heap_size++] = k;
    
    // heapify up
    for (auto current = heap_size - 1; current != 0; ) {
        const auto parent = parentIndexOf(current);
        if (harr[parent] <= harr[current]) break;
        swap(harr[current], harr[parent]);
        current = parent;
    }
}
