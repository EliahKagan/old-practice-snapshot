#include <cstdio>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
};

void Print(Node *head)
{
    if (head) {
        printf("%d\n", head->data);
        Print(head->next);
    }
}
