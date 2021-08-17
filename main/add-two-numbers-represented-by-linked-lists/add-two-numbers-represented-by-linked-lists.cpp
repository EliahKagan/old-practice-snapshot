/*
struct node
{
    int data;
    struct node* next;
}; */


//write a function returns the resultant linked list

node* addTwoLists(node* first, node* second)
{
    constexpr auto base = 10;
    
    const auto head = new node{0, nullptr};
    auto cur = head;
    node* prev {nullptr};
    
    while (first != nullptr && second != nullptr) {
        const auto digit_sum = cur->data + first->data + second->data;
        cur->data = digit_sum % base;
        cur->next = new node{digit_sum / base, nullptr};
        
        prev = cur;
        cur = cur->next;
        first = first->next;
        second = second->next;
    }
    
    for (auto rest = (first == nullptr ? second : first); rest != nullptr; ) {
        const auto digit_sum = cur->data + rest->data;
        cur->data = digit_sum % base;
        cur->next = new node{digit_sum / base, nullptr};
        
        prev = cur;
        cur = cur->next;
        rest = rest->next;
    }
    
    if (cur->data == 0 && prev != nullptr) { // should drop high-order zero
        prev->next = nullptr;
        delete cur;
    }
    
    return head;
}
