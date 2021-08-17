#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

static struct node *read_list()
{
    struct node start = {0, NULL}, *cur = &start;
    
    int n = 0;
    for ((void)scanf("%d", &n); n > 0; --n) {
        cur = cur->next = calloc(1, sizeof *cur->next);
        if (cur == NULL) abort();
        (void)scanf("%d", &cur->data);
    }
    
    return start.next;
}

static void write_list(const struct node *head)
{
    if (head != NULL) {
        printf("%d", head->data);
        while ((head = head->next) != NULL) printf(" %d", head->data);
    }
    
    putchar('\n');
}

static void delete_list(struct node *head)
{
    while (head != NULL) {
        struct node *const next = head->next;
        free(head);
        head = next;
    }
}

static struct node *segregate_even_odd(struct node *head)
{
    struct node evens = {0, NULL}, *ep = &evens, odds = {0, NULL}, *op = &odds;
    
    for (; head != NULL; head = head->next) {
        if (head->data % 2 == 0)    ep = ep->next = head;
        else                        op = op->next = head;
    }
    
    ep->next = odds.next; // last even => first odd
    op->next = NULL;      // last odd => end
    
    return evens.next;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        struct node *head = segregate_even_odd(read_list());
        write_list(head);
        delete_list(head);
    }
}
