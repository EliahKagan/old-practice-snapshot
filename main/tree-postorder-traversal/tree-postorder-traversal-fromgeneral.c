#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {

    int data;
    struct node *left;
    struct node *right;

};

struct node* insert( struct node* root, int data ) {

	if(root == NULL) {

        struct node* node = (struct node*)malloc(sizeof(struct node));

        node->data = data;

        node->left = NULL;
        node->right = NULL;
        return node;

	} else {

		struct node* cur;

		if(data <= root->data) {
            cur = insert(root->left, data);
            root->left = cur;
		} else {
            cur = insert(root->right, data);
            root->right = cur;
		}

		return root;
	}
}

/* you only have to complete the function given below.
node is defined as

struct node {

    int data;
    struct node *left;
    struct node *right;

};

*/

#include <assert.h>
#include <stdbool.h>

static inline void *xrealloc(void *const p, const size_t n)
{
    void *const ret = realloc(p, n);
    if (!ret) abort();
    return ret;
}

typedef const struct node *Element;

struct stack {
    Element *elems;
    int size;
    int capacity;
};

static inline struct stack stack_init(void)
{
    return (struct stack){NULL, 0, 0};
}

static void stack_free(struct stack *const sp)
{
    free(sp->elems);
    sp->elems = NULL;

    sp->size = sp->capacity = 0;
}

static void stack_detail_expand(struct stack *const sp)
{
    enum { initial_capacity = 1 };

    assert(sp->capacity >= 0);
    sp->capacity = (sp->capacity == 0 ? initial_capacity : sp->capacity * 2);
    sp->elems = xrealloc(sp->elems, sp->capacity * sizeof *sp->elems);
}

static inline void stack_push(struct stack *const sp, const Element value)
{
    assert(0 <= sp->size && sp->size <= sp->capacity);
    if (sp->size == sp->capacity) stack_detail_expand(sp);
    sp->elems[sp->size++] = value;
}

static inline void stack_pop(struct stack *const sp)
{
    assert(sp->size > 0);
    --sp->size;
}

static inline Element stack_top(const struct stack *const sp)
{
    assert(sp->size > 0);
    return sp->elems[sp->size - 1];
}

static inline bool stack_empty(const struct stack *const sp)
{
    assert(sp->size >= 0);
    return sp->size == 0;
}

typedef void (*Action)(int);

static void dfs(const struct node *root,
                const Action f_pre, const Action f_in, const Action f_post)
{
    struct stack s = stack_init();
    const struct node *post = NULL;

    while (root || !stack_empty(&s)) {
        // Go left as far as possible, doing the preorder task at each node.
        for (; root; root = root->left) {
            f_pre(root->data);
            stack_push(&s, root);
        }

        const struct node *const cur = stack_top(&s);

        if (!cur->right || cur->right != post) {
            // The right subtree is unexplored. Do the inorder task.
            f_in(cur->data);
        }

        if (!cur->right || cur->right == post) {
            // The right subtree is explored. Do the postorder task and retreat.
            post = cur;
            f_post(post->data);
            stack_pop(&s);
        } else {
            // The right subtree is nonempty and unvisited. Go there next.
            root = cur->right;
        }
    }

    stack_free(&s);
}

static void noop(const int data)
{
    (void)data;
}

static void display(const int data)
{
    printf("%d ", data);
}

void preOrder(const struct node *const root)
{
    dfs(root, display, noop, noop);
}

void inOrder(const struct node *const root)
{
    dfs(root, noop, display, noop);
}

void postOrder(const struct node *const root)
{
    dfs(root, noop, noop, display);
}


int main() {

    struct node* root = NULL;

    int t;
    int data;

    scanf("%d", &t);

    while(t-- > 0) {
        scanf("%d", &data);
        root = insert(root, data);
    }

	preOrder(root);
    return 0;
}
