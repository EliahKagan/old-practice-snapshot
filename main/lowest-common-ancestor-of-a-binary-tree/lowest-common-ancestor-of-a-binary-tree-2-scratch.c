#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static bool contains(const struct TreeNode *const root,
                     const struct TreeNode *const node)
{
    return root != NULL && (root == node || contains(root->left, node)
                                         || contains(root->right, node));
}

struct AncestorInfo {
    struct TreeNode *node;
    bool is_common;
};

static struct AncestorInfo ancestor(struct TreeNode *const root,
        struct TreeNode *const p, struct TreeNode *const q)
{
    if (root == NULL) return (struct AncestorInfo) { NULL, false };

    if (root == p) {
        return (struct AncestorInfo)
               { root, contains(root->left, q) || contains(root->right, q) };
    }

    if (root == q) {
        return (struct AncestorInfo)
               { root, contains(root->left, p) || contains(root->right, p) };
    }

    const struct AncestorInfo leftInfo = ancestor(root->left, p, q);
    if (leftInfo.is_common) return leftInfo;

    // TODO: maybe eliminate this tail call using a loop (or possibly goto)
    if (leftInfo.node == NULL) return ancestor(root->right, p, q);

    return (struct AncestorInfo)
           { root, contains(root->right, (leftInfo.node == p ? q : p)) };

}

struct TreeNode *lowestCommonAncestor(struct TreeNode *const root,
        struct TreeNode *const p, struct TreeNode *const q)
{
    if (p == q) return contains(root, p) ? p : NULL;

    const struct AncestorInfo rootInfo = ancestor(root, p, q);
    return rootInfo.is_common ? rootInfo.node : NULL;
}

static void printInorder(const struct TreeNode *const root)
{
    if (root != NULL) {
        printInorder(root->left);
        printf("%d ", root->val);
        printInorder(root->right);
    }
}

static void pretest()
{
    enum { len = 6 };
    struct TreeNode nodes[len] = { 0 };
    int i = 0;

    struct TreeNode *const root = &nodes[i++];
    struct TreeNode *const left = &nodes[i++];
    struct TreeNode *const right = &nodes[i++];
    struct TreeNode *const leftLeft = &nodes[i++];
    struct TreeNode *const leftRight = &nodes[i++];
    struct TreeNode *const leftLeftLeft = &nodes[i++];

    assert(i == len);

    root->val = -1;
    root->left = left;
    root->right = right;

    left->val = 0;
    left->left = leftLeft;
    left->right = leftRight;

    right->val = 3;

    leftLeft->val = -2;
    leftLeft->left = leftLeftLeft;

    leftRight->val = 4;

    leftLeftLeft->val = 8;

    printInorder(root);
    printf("\n\n");

    const struct TreeNode *const result =
            lowestCommonAncestor(root, leftLeftLeft, leftRight);

}

static void test()
{
    struct TreeNode nodes[] = { { 0, NULL, NULL },
                                { 1, &nodes[0], &nodes[8] },
                                { 2, &nodes[7], &nodes[4] },
                                { 3, &nodes[5], &nodes[1] },
                                { 4, NULL, NULL },
                                { 5, &nodes[6], &nodes[2] },
                                { 6, NULL, NULL },
                                { 7, NULL, NULL },
                                { 8, NULL, NULL} };

    struct TreeNode *const root = &nodes[3];
    
    printInorder(root);
    printf("\n\n");

    printf("%d\n", lowestCommonAncestor(root, &nodes[5], &nodes[1])->val);
    printf("%d\n", lowestCommonAncestor(root, &nodes[5], &nodes[4])->val);
    printf("%d\n", lowestCommonAncestor(root, &nodes[6], &nodes[7])->val);
    printf("%d\n", lowestCommonAncestor(root, &nodes[8], &nodes[8])->val);
    printf("%d\n", lowestCommonAncestor(root, &nodes[8], &nodes[0])->val);

    printf("(%d)\n\n", !lowestCommonAncestor(&nodes[5], &nodes[2], &nodes[1]));
}

int main(void)
{
    pretest();
    test();
}
