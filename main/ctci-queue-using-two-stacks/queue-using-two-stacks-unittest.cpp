#include <cstdlib>
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
}

int main(int, char **argv)
{
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    while (!q.empty()) std::cout << q.dequeue() << '\n';

    try {
        Queue<const char*> r;
        r.enqueue("first");
        r.enqueue("second");
        r.enqueue("third");
        std::cout << r.dequeue() << '\n'; // first
        std::cout << r.peek() << '\n'; // second
        r.enqueue("fourth");
        std::cout << r.dequeue() << '\n'; // second
        r.enqueue("fifth");
        std::cout << r.dequeue() << '\n'; // third
        std::cout << r.dequeue() << '\n'; // fourth
        r.enqueue("sixth");
        std::cout << r.peek() << '\n'; // fifth
        std::cout << r.dequeue() << '\n'; // fifth
        std::cout << r.dequeue() << '\n'; // sixth
        std::cout << r.dequeue() << '\n'; // ERROR
    }
    catch (const NoElementException& e) {
        std::cerr << argv[0] << ": error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    std::cout << "Done.\n";
    return EXIT_SUCCESS;
}
