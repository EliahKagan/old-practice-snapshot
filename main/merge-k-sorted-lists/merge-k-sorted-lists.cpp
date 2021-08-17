/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // fill a vector with all items from all lists
        vector<ListNode*> a;
        for (auto head : lists)
            for (; head != nullptr; head = head->next) a.push_back(head);

        // if there were no nodes, we're done
        if (a.empty()) return nullptr;

        // sort it by each item's val member (std::sort implementations
        // tend to perform very well with partially sorted data)
        sort(begin(a), end(a), [](ListNode *const x, ListNode *const y) {
            return x->val < y->val;
        });

        // connect the nodes
        a.push_back(nullptr);
        for (auto p = cbegin(a), q = next(p); ((*p)->next = *q) != nullptr;
                                              ++p, ++q) { }

        // return the head
        return a.front();
    }
};
