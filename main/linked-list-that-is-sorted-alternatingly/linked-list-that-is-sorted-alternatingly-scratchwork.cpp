#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

namespace {
    struct Node {
        int data;
        Node* next;
    };
    
    Node* create_list(const int x)
    {
        return new Node{x, nullptr};
    }
    
    template<typename... Ints>
    Node* create_list(const int head, Ints... tail)
    {
        return new Node{head, create_list(tail...)};
    }
    
    void destroy_list(Node*& head)
    {
        if (head != nullptr) {
            destroy_list(head->next);
            delete head;
            head = nullptr;
        }
    }
    
    tuple<Node*, Node*> unzip(Node* head)
    {
        Node a {0, nullptr}, b {0, nullptr};
        
        for (auto p = &a, q = &b; head != nullptr; swap(p, q)) {
            p = p->next = head;
            head = head->next;
            p->next = nullptr;
        }
        
        return make_tuple(a.next, b.next);
    }
    
    Node* reverse(Node* head)
    {
        Node* prev {nullptr};
        
        while (head != nullptr) {
            const auto next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        
        return prev;
    }
    
    Node* merge(Node* p, Node* q)
    {
        Node fake_head {0, nullptr};
        
        auto tail = &fake_head;
        
        while (p != nullptr && q != nullptr) {
            if (p->data > q->data) swap(p, q);
            tail = tail->next = p;
            p = p->next;
            tail->next = nullptr;
        }
        
        if (p == nullptr) swap(p, q);
        tail->next = p;
        
        return fake_head.next;
    }
    
    void print(const char* const name, const Node* head)
    {
        cout << name << ": ";
        for (; head != nullptr; head = head->next) cout << head->data << ' ';
        cout << '\n';
    }
}

int main()
{
    cout << "Creating the list.\n";
    auto p = create_list(10, 40, 53, 30, 67, 12, 89);
    print("p", p);
    
    cout << "Unzipping p into q and r.\n";
    decltype(p) q, r;
    tie(q, r) = unzip(p);
    print("q", q);
    print("r", r);
    
    cout << "Reversing r.\n";
    r = reverse(r);
    print("r", r);
    
    cout << "Merging q and r and assigning the result back to p.\n";
    p = merge(q, r);
    print("p", p);
    
    cout << "Done.\n";
    destroy_list(p);
}
