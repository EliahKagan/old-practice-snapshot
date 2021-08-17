#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

static struct node *make_node(const int data, struct node *const next)
{
    struct node *const p = malloc(sizeof *p);
    if (p == NULL) abort();
    
    p->data = data;
    p->next = next;
    
    return p;
}

static struct node *create_list(int len, ...)
{
    struct node fake_head = { 0, NULL };
    
    va_list v;
    va_start(v, len);
    
    for (struct node *p = &fake_head; len-- > 0; p = p->next)
        p->next = make_node(va_arg(v, int), NULL);
    
    va_end(v);
    
    return fake_head.next;
}

static void destroy_list(struct node *head)
{
    while (head != NULL) {
        struct node *next = head->next;
        free(head);
        head = next;
    }
}

static void print(const struct node *head)
{
    printf("[ ");
    for (; head != NULL; head = head->next) printf("%d ", head->data);
    printf("]\n");
}

// Terminate the list after the first k nodes, and return a list made of the
// remaining nodes. If there are fewer than (or equal to) k nodes in the list,
// then the list is not modified and NULL is returned.
static struct node *split(struct node* head, int k)
{
    for (; k > 1 && head != NULL; --k) head = head->next;
    if (head == NULL) return NULL;

    struct node *const next = head->next;
    head->next = NULL;
    return next;
}

// Reverses the list completely, in the usual way. Returns the new head.
static struct node *rev(struct node* head)
{
    struct node *acc = NULL;
    
    while (head != NULL) {
        struct node *const next = head->next;
        head->next = acc;
        acc = head;
        head = next;
    }
    
    return acc;
}

static void test_rev(void)
{
    struct node *head = create_list(8, 1, 2, 2, 4, 5, 6, 7, 8);
    print(head);
    head = rev(head);
    print(head);
    destroy_list(head);
}

static void test_split(void)
{
    struct node *head = create_list(8, 1, 2, 2, 4, 5, 6, 7, 8);
    struct node *next_group = split(head, 4);

    print(head);
    print(next_group);

    destroy_list(head);
    destroy_list(next_group);
}

int main(void)
{
    test_rev();
    putchar('\n');
    test_split();
}
