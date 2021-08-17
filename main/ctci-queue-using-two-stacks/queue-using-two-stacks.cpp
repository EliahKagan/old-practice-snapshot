#include <iostream>
#include <stack>
#include <stdexcept>

namespace {
    class NoElementException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    template<typename T>
    class Queue {
    public:
        Queue() = default;
        Queue(const Queue<T>&) = delete;
        Queue(Queue<T>&&) = delete;
        Queue<T>& operator=(const Queue<T>&) = delete;
        Queue<T>& operator=(Queue<T>&&) = delete;

        bool empty() const;
        typename std::stack<T>::size_type size() const;

        void enqueue(const T x);
        T peek();
        T dequeue();

    private:
        std::stack<T> in {}, out {};

        void recharge();
    };

    template<typename T>
    bool Queue<T>::empty() const
    {
        return out.empty() && in.empty();
    }

    template<typename T>
    typename std::stack<T>::size_type Queue<T>::size() const
    {
        return out.size() + in.size();
    }

    template<typename T>
    void Queue<T>::enqueue(const T x)
    {
        in.push(x);
    }

    template<typename T>
    T Queue<T>::peek()
    {
        recharge();
        return out.top();
    }

    template<typename T>
    T Queue<T>::dequeue()
    {
        const auto ret = peek();
        out.pop();
        return ret;
    }

    template<typename T>
    void Queue<T>::recharge()
    {
        if (!out.empty()) return;

        if (in.empty())
            throw NoElementException{"can't access element from empty queue"};

        do {
            out.push(in.top());
            in.pop();
        }
        while (!in.empty());
    }

    int get()
    {
        auto x = 0;
        std::cin >> x;
        return x;
    }
}

int main()
{
    Queue<int> iq;

    for (auto q = get(); q > 0; --q) {
        switch (get()) {
        case 1:
            iq.enqueue(get());
            continue;

        case 2:
            iq.dequeue();
            continue;

        case 3:
            std::cout << iq.peek() << '\n';
            continue;

        default:
            throw std::invalid_argument{"unrecognized query type"};
        }
    }
}
