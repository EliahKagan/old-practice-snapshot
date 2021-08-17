#include "linked-list-that-is-sorted-alternatingly.h" //#include<bits/stdc++.h>
using namespace std;

struct Node
{
	int data;
	struct Node *next;
};

void sort(Node **head);

// A utility function to create a new node
Node* newNode(int key)
{
	Node *temp = new Node;
	temp->data = key;
	temp->next = NULL;
	return temp;
}

void append(struct Node** headRef, int newData)
{
	struct Node* new_node = newNode(newData);
	struct Node *last = *headRef;
	if (*headRef == NULL)
	{
	    *headRef = new_node;
	    return;
	}
	while (last->next != NULL)last = last->next;
	last->next = new_node;
}

// A utility function to print a linked list
void printList(Node *head)
{
	while (head != NULL)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

int main()
{
	int test;
	cin>>test;
	while(test--)
	{
	    struct Node* head = NULL;
	    int n, k;
	    cin>>n;
	    for(int i=0; i<n ;i++){
	        cin>>k;
	        append(&head, k);
	    }
	    sort(&head);
	    printList(head);
	}
	return 0;
}

/*Structure of Node of the linked list is as
struct Node
{
	int data;
	struct Node *next;
};
*/

namespace {
    tuple<Node*, Node*> unzip(Node* head)
    {
        Node a {0, nullptr}, b {0, nullptr};
        
        for (auto p = &a, q = &b; head != nullptr; swap(p, q)) {
            p = p->next = head;
            head = head->next;
            p->next = nullptr;
        }
        
        return make_tuple(a.next, b.next);
    }
    
    Node* reverse(Node* head)
    {
        Node* prev {nullptr};
        
        while (head != nullptr) {
            const auto next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        
        return prev;
    }
    
    Node* merge(Node* p, Node* q)
    {
        Node fake_head {0, nullptr};
        
        auto tail = &fake_head;
        
        while (p != nullptr && q != nullptr) {
            if (p->data > q->data) swap(p, q);
            tail = tail->next = p;
            p = p->next;
            tail->next = nullptr;
        }
        
        if (p == nullptr) swap(p, q);
        tail->next = p;
        
        return fake_head.next;
    }
}

void sort(Node** const headp)
{
    Node* p {}, * q {};
    tie(p, q) = unzip(*headp);
    *headp = merge(p, reverse(q));
}
