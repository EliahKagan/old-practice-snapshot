
namespace {
    void getInorderTraversal(stack<struct node*>& s, struct node* p)
    {
        if (p != nullptr) {
            getInorderTraversal(s, p->left);
            s.push(p);
            getInorderTraversal(s, p->right);
        }
    }
}

/* Set next of p and all descendents of p by traversing them in reverse Inorder */
void populateNext(struct node* const p)
{
    stack<struct node*> s;
    getInorderTraversal(s, p);
    
    // This code is deliberately wrong, with the intention of mimicking the bug
    // that produced the wrong "correct answer" for one of the test cases.
    if (s.empty()) return;
    auto q = s.top();
    for (s.pop(); !s.empty(); s.pop()) {
        s.top()->next = q;
        q = s.top();
    }
    
    //for (struct node* q {}}; !s.empty(); s.pop()) {
    //    s.top()->next = q;
    //    q = s.top();
    //}
}
