/*The structure of the Node is
struct Node
{
    int data;
    struct Node* next;
};*/

#include <vector>

namespace {
    template<typename T>
    bool isPalindrome(const std::vector<T>& a)
    {
        if (a.size() < 2u) return true;
        
        for (auto p = a.cbegin(), q = a.cend(); p < --q; ++p)
            if (*p != *q) return false;
        
        return true;
    }
}

/*You are required to complete this method */
bool isPalindrome(Node *head)
{
    std::vector<decltype(head->data)> a;
    for (; head != nullptr; head = head->next) a.push_back(head->data);
    return isPalindrome(a);
}
