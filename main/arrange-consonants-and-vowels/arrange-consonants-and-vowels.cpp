/*
Structure of the node of the linked list is as
struct Node
{
	char data;
	struct Node *next;
};
*/

namespace {
    inline bool is_vowel(const char ch)
    {
        switch (ch) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
            
        default:
            return false;
        }
    }
    
    inline void pop_front_push_back(Node*& dest_tail, Node*& src_head)
    {
        dest_tail = dest_tail->next = src_head;
        src_head = src_head->next;
        dest_tail->next = nullptr;
    }
}

// task is to complete this function
// function should return head to the list after making 
// necessary arrangements
Node* arrange(Node* head)
{
    Node vowels {'\0', nullptr}, consonants {'\0', nullptr};
    auto vow = &vowels, con = &consonants;
    
    while (head != nullptr)
        pop_front_push_back((is_vowel(head->data) ? vow : con), head);
    
    vow->next = consonants.next;
    return vowels.next;
}
