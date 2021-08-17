class MyCircularDeque {
public:
    /** Initializes the circular deque data structure with the specified capacity. */
    explicit MyCircularDeque(int capacity);

    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) noexcept;

    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) noexcept;

    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() noexcept;

    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() noexcept;

    /** Get the front item from the deque. */
    int getFront() const noexcept;

    /** Get the last item from the deque. */
    int getRear() const noexcept;

    /** Checks whether the circular deque is empty or not. */
    constexpr bool isEmpty() const noexcept;

    /** Checks whether the circular deque is full or not. */
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

MyCircularDeque::MyCircularDeque(const int capacity)
    : elems_(static_cast<size_t>(check_capacity(capacity)))
{
}

inline bool MyCircularDeque::insertFront(const int value) noexcept
{
    if (isFull()) return false;

    ++size_;
    front_index_ = index(-1);
    elems_[front_index_] = value;
    return true;
}

inline bool MyCircularDeque::insertLast(const int value) noexcept
{
    if (isFull()) return false;

    elems_[index(size_++)] = value;
    return true;
}

inline bool MyCircularDeque::deleteFront() noexcept
{
    if (isEmpty()) return false;

    --size_;
    front_index_ = index(1);
    return true;
}

inline bool MyCircularDeque::deleteLast() noexcept
{
    if (isEmpty()) return false;

    --size_;
    return true;
}

inline int MyCircularDeque::getFront() const noexcept
{
    return isEmpty() ? no_element : elems_[front_index_];
}

inline int MyCircularDeque::getRear() const noexcept
{
    return isEmpty() ? no_element : elems_[index(size_ - 1)];
}

constexpr bool MyCircularDeque::isEmpty() const noexcept
{
    return size_ == 0;
}

inline bool MyCircularDeque::isFull() const noexcept
{
    return size_ == capacity();
}

inline int MyCircularDeque::check_capacity(const int capacity)
{
    if (capacity <= 0)
        throw length_error{"capacity must be strictly positive"};

    return capacity;
}

inline int MyCircularDeque::capacity() const noexcept
{
    return static_cast<int>(elems_.size());
}

inline int MyCircularDeque::index(const int ordinal) const noexcept
{
    return (capacity() + front_index_ + ordinal) % capacity();
}

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque obj = new MyCircularDeque(k);
 * bool param_1 = obj.insertFront(value);
 * bool param_2 = obj.insertLast(value);
 * bool param_3 = obj.deleteFront();
 * bool param_4 = obj.deleteLast();
 * int param_5 = obj.getFront();
 * int param_6 = obj.getRear();
 * bool param_7 = obj.isEmpty();
 * bool param_8 = obj.isFull();
 */
