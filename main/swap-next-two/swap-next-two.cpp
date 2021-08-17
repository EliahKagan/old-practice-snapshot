//clang 3.8.0

#include <iostream>

namespace {
    struct Node {
        char data;
        Node* next;
        
        ~Node() { delete next; }
    };
    
    void print(Node* p)
    {
        for (; p != nullptr; p = p->next) std::cout << p->data << ' ';
        std::cout << '\n';
    }
    
    void swap_next_two(Node* const p)
    {
        const auto q = p->next, r = q->next, s = r->next;
        p->next = r;
        r->next = q;
        q->next = s;
    }
}

int main()
{
    auto p = new Node{'A', new Node{'B', new Node{'C', new Node{'D', nullptr}}}};
    
    print(p);
    swap_next_two(p);
    print(p);
    
    delete p;
}
