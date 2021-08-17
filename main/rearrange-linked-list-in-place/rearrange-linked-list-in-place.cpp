#include <cassert>

struct Node {
    int data;
    Node* next;
};

namespace {
    Node* split(Node* head) // returns head of second sublist
    {
        Node* prev {nullptr};
        
        for (auto fast = head; fast != nullptr && fast->next != nullptr;
                               fast = fast->next->next) {
            prev = head;
            head = head->next;
        }
        
        if (prev != nullptr) prev->next = nullptr;
        return head;
    }
    
    inline void rev_step(Node*& acc, Node*& cur)
    {
        const auto head = cur;
        cur = cur->next;
        head->next = acc;
        acc = head;
    }
    
    Node* rev(Node* acc, Node* cur)
    {
        while (cur != nullptr) rev_step(acc, cur);
        return acc;
    }
    
    inline Node* reverse(Node* const head)
    {
        return rev(nullptr, head);
    }
    
    Node* interleave(Node* fst, Node* snd)
    {
        if (fst == nullptr) return snd;
        if (snd == nullptr) return fst;
        
        const auto head = fst;
        
        while (fst->next != nullptr && snd->next != nullptr) {
            const auto snd_next = snd->next;
            snd->next = fst->next;
            fst->next = snd;
            fst = snd->next;
            snd = snd_next;
        }
        
        if (snd->next == nullptr) snd->next = fst->next;
        fst->next = snd;
        
        return head;
    }
}

Node* inPlace(Node* const head)
{
    const auto ret = (head == nullptr || head->next == nullptr
                        ? head
                        : interleave(head, reverse(split(head))));
    assert(ret == head);
    return ret;
}
