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
    static int numComponents(const ListNode* head, const vector<int>& g);
};

int Solution::numComponents(const ListNode* head, const vector<int>& g)
{
    const unordered_set<int> sg (cbegin(g), cend(g));

    auto cnt = 0;

    auto in = false;
    for (; head; head = head->next) {
        if (sg.count(head->val)) {
            in = true;
        }
        else if (in) {
            in = false;
            ++cnt;
        }
    }

    if (in) ++cnt;
    return cnt;
}
