#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32
#include <alloca.h>
#elif defined(_MSC_VER)
#include <malloc.h>
#endif

enum constants {
    k_nmax = 5000
};

enum opcodes {
    k_opcode_unread_to_read = 1,
    k_opcode_read_to_trash = 2,
    k_opcode_unread_to_trash = 3,
    k_opcode_trash_to_read = 4
};

struct node {
    int prev, next;
};

static void splice_left(struct node *const nodes,
                        const int dest, const int src)
{
    nodes[nodes[src].prev].next = nodes[src].next;
    nodes[nodes[src].next].prev = nodes[src].prev;

    nodes[src].prev = nodes[dest].prev;
    nodes[src].next = dest;

    nodes[nodes[dest].prev].next = src;
    nodes[dest].prev = src;
}

static void print(const struct node *const nodes, const int sentinel)
{
    int i = nodes[sentinel].next;

    if (i == sentinel) {
        puts("EMPTY");
        return;
    }

    printf("%d", i);
    while ((i = nodes[i].next) != sentinel) printf(" %d", i);
    putchar('\n');
}

static inline void initialize_list(struct node *const nodes, const int n)
{
    nodes[0].prev = n;
    nodes[0].next = 1;

    for (int i = 1; i != n; ++i) {
        nodes[i].prev = i - 1;
        nodes[i].next = i + 1;
    }

    nodes[n].prev = n - 1;
    nodes[n].next = 0;
}

static inline void initialize_sentinel(struct node *const nodes,
                                       const int sentinel)
{
    nodes[sentinel].prev = nodes[sentinel].next = sentinel;
}

static inline void perform_queries(const int n, struct node *const nodes,
                                   const int read, const int trash, int q)
{
    while (q-- != 0) {
        int op = 0, arg = 0; 
        (void)scanf("%d%d", &op, &arg);
        if (!(0 < arg && arg <= n)) abort(); // message ID is out of range

        switch (op) {
        case k_opcode_unread_to_read:
        case k_opcode_trash_to_read:
            splice_left(nodes, read, arg);
            break;

        case k_opcode_read_to_trash:
        case k_opcode_unread_to_trash:
            splice_left(nodes, trash, arg);
            break;

        default:
            abort(); // invalid opcode specified
        }
    }
}

static void run()
{
    // Read list length and number of queries.
    int n = 0, q = 0;
    (void)scanf("%d%d", &n, &q);
    if (!(0 < n && n <= k_nmax && 0 <= q)) abort();

    // Define the special nodes' indices and create the list.
    const int unread = 0, read = n + 1, trash = n + 2; // special indices
    struct node *const nodes = alloca((size_t)(n + 3) * sizeof nodes[0]);

    // Initialize all nodes by setting their prev and next connections.
    initialize_list(nodes, n);
    initialize_sentinel(nodes, read);
    initialize_sentinel(nodes, trash);

    // Move nodes between lists as specified in the queries.
    perform_queries(n, nodes, read, trash, q);

    // Print each list.
    print(nodes, unread);
    print(nodes, read);
    print(nodes, trash);
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) run();
}
