#include "delete-nodes-having-greater-value-on-right.h" //#include<bits/stdc++.h>

using namespace std;

struct Node
{
int data;
Node* next;
};

Node *newNode(int data)
{
    Node *new_node = new Node;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}


void print(Node *root)
{
Node *temp = root;
while(temp!=NULL)
{
cout<<temp->data<<" ";
temp=temp->next;
}
}


Node *compute(Node *head);

int main()
{
    int T;
	cin>>T;

	while(T--)
	{
		int K;
		cin>>K;
		struct Node *head = NULL;
        struct Node *temp = head;

		for(int i=0;i<K;i++){
		int data;
		cin>>data;
			if(head==NULL)
			head=temp=newNode(data);
			else
			{
				temp->next = newNode(data);
				temp=temp->next;
			}
		}

        Node *result = compute(head);
        print(result);
        cout<<endl;
    }
}


/*

The structure of linked list is the following

struct Node
{
int data;
Node* next;
};

*/

namespace {
    vector<int> toVector(const Node *head)
    {
        vector<int> a;
        for (; head != nullptr; head = head->next) a.push_back(head->data);
        return a;
    }
    
    void maxFillBack(vector<int>& a)
    {
        auto maxval = numeric_limits<int>::min();
        
        const auto q = a.rend();
        for (auto p = a.rbegin(); p != q; ++p) {
            if (*p < maxval) *p = maxval;
            else maxval = *p;
        }
    }
    
    vector<int> getBounds(const Node *const head)
    {
        auto a = toVector(head);
        maxFillBack(a);
        return a;
    }
}

Node *compute(Node *const head)
{
    Node start {0, head}, *prev = &start;
    
    for (const auto bound : getBounds(head)) {
        const auto cur = prev->next;

        if (cur->data < bound) {
            prev->next = cur->next;
            delete cur;
        }
        else prev = cur;
    }

    return start.next;
}
