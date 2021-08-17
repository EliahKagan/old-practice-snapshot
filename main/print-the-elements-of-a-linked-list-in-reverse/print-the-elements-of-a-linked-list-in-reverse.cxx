#include <cstdio>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
};

void ReversePrint(Node *head)
{
    if (head) {
        if (head->next) ReversePrint(head->next);
        printf("%d\n", head->data);
    }
}
