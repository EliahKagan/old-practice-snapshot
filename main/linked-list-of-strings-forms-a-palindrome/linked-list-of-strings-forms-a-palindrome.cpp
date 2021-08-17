/*

The structure of linked list is the following

struct Node
{
String data;
Node* next;
};

*/

namespace {
    string join(const Node* head)
    {
        ostringstream out;
        for (; head != nullptr; head = head->next) out << head->data;
        return out.str();
    }
    
    bool isPalindrome(const string& text)
    {
        if (text.size() < 2u) return true;
        
        for (auto p = text.cbegin(), q = text.cend(); p < --q; ++p)
            if (*p != *q) return false;
        
        return true;
    }
}

bool Compute(Node* const head)
{
    return isPalindrome(join(head));
}
