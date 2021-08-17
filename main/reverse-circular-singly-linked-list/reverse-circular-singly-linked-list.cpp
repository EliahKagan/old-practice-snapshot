#include <array>
#include <cstddef>
#include <iostream>

namespace {
    struct Node {
        int data;
        Node* next;
    };

    void print(const Node* const head)
    {
        std::cout << head->data;
        for (auto cur = head->next; cur != head; cur = cur->next)
            std::cout << ' ' << cur->data;

        std::cout << '\n';
    }

    void reverse(Node** const head_ref)
    {
        const auto head = *head_ref;
        auto acc = head;

        for (auto cur = head->next; ; ) {
            const auto next = cur->next;
            cur->next = acc;
            acc = cur;

            if (cur == head) break;
            cur = next;
        }

        *head_ref = head->next;
    }
}

int main()
{
    std::array<Node, 6> nodes {};

    for (std::size_t i {0u}; i != nodes.size(); ++i) {
        nodes[i].data = (static_cast<int>(i) + 1) * 10;
        nodes[i].next = &nodes[i] + 1;
    }

    nodes.back().next = &nodes.front();

    auto head = &nodes.front();
    print(head);

    reverse(&head);
    print(head);
}
