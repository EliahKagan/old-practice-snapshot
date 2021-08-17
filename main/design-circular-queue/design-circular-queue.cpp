class MyCircularQueue {
public:
    /** Initializes the circular deque data structure with the specified capacity. */
    MyCircularQueue(int capacity);

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) noexcept;

    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() noexcept;

    /** Get the front item from the queue. */
    int Front() const noexcept;

    /** Get the last item from the queue. */
    int Rear() const noexcept;

    /** Checks whether the circular queue is empty or not. */
    constexpr bool isEmpty() const noexcept;

    /** Checks whether the circular queue is full or not. */
    bool isFull() const noexcept;

private:
    static constexpr auto no_element = -1;

    static int check_capacity(int capacity);

    int capacity() const noexcept;

    int index(int ordinal) const noexcept;

    vector<int> elems_;
    int size_ {};
    int front_index_ {};
};

MyCircularQueue::MyCircularQueue(const int capacity)
    : elems_(static_cast<size_t>(check_capacity(capacity)))
{
}

inline bool MyCircularQueue::enQueue(const int value) noexcept
{
    if (isFull()) return false;

    elems_[index(size_++)] = value;
    return true;
}

inline bool MyCircularQueue::deQueue() noexcept
{
    if (isEmpty()) return false;

    --size_;
    front_index_ = index(1);
    return true;
}

inline int MyCircularQueue::Front() const noexcept
{
    return isEmpty() ? no_element : elems_[front_index_];
}

inline int MyCircularQueue::Rear() const noexcept
{
    return isEmpty() ? no_element : elems_[index(size_ - 1)];
}

constexpr bool MyCircularQueue::isEmpty() const noexcept
{
    return size_ == 0;
}

inline bool MyCircularQueue::isFull() const noexcept
{
    return size_ == capacity();
}

inline int MyCircularQueue::check_capacity(const int capacity)
{
    if (capacity <= 0)
        throw length_error{"capacity must be strictly positive"};

    return capacity;
}

inline int MyCircularQueue::capacity() const noexcept
{
    return static_cast<int>(elems_.size());
}

inline int MyCircularQueue::index(const int ordinal) const noexcept
{
    return (capacity() + front_index_ + ordinal) % capacity();
}

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
