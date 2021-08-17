#include "intersection-of-two-linked-list.h" //#include<bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	struct node* next;
};

void printList(struct node *node)
{
    while(node!=NULL){
        cout<<node->data<<' ';
        node = node->next;
    }
    printf("\n");
}

void push(struct node** head_ref, int new_data)
{
    struct node* new_node =	(struct node*) malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

struct node* findIntersection(struct node* head1, struct node* head2);

int main()
{
    long test;
    cin>>test;
    while(test--)
    {
        struct node* a = NULL;
        struct node* b = NULL;
        int n, m, tmp;
        cin>>n;
        for(int i=0; i<n; i++)
        {
            cin>>tmp;
            push(&a, tmp);
        }
        cin>>m;
        for(int i=0; i<m; i++)
        {
            cin>>tmp;
            push(&b, tmp);
        }
        printList(findIntersection(a, b));
    }
    return 0;
}

namespace {
    vector<int> asSortedVector(const struct node* src)
    {
        vector<int> dest;
        for (; src != nullptr; src = src->next) dest.push_back(src->data);
        sort(begin(dest), end(dest));
        return dest;
    }
    
    // Output iterator for inserting elements at the front of a list.
    class NodeIter
            : public iterator<output_iterator_tag, void, void, int*, int&> {
    public:
        explicit NodeIter(struct node* head = nullptr) : head_{head} { }
        
        NodeIter& operator++() { return *this; } // no-op, like front_inserter
        NodeIter& operator++(int) { return *this; } // same deal
        
        int& operator*()
        {
            head_ = makeNode(head_); // *p makes element, like front_inserter
            return head_->data;
        }
        
        struct node* get_node() { return head_; }
    
    private:
        // Create a new list node with 0 data and the specified next pointer.
        static struct node* makeNode(struct node* const next)
        {
            // The test harness makes nodes freeable with free(); so I am too.
            const auto p =
                    static_cast<struct node*>(calloc(1u, sizeof(struct node)));
            
            if (p == nullptr) throw bad_alloc{};
            
            p->next = next;
            return p;
        }
    
        struct node* head_;
    };
}

/*
structure of the node is as
struct node
{
	int data;
	struct node* next;
};
*/
struct node* findIntersection(struct node* head1, struct node* head2)
{
    const auto a = asSortedVector(head1), b = asSortedVector(head2);
    
    return set_intersection(a.crbegin(), a.crend(), b.crbegin(), b.crend(),
                            NodeIter{}, greater<int>{}).get_node();
}
