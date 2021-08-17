/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {TreeNode} root
 * @param {number} key
 * @return {TreeNode}
 */
function deleteNode(root, key) {
    'use strict';

    if (!root) return null;

    if (key < root.val) {
        root.left = deleteNode(root.left, key);
        return root;
    }

    if (root.val < key) {
        root.right = deleteNode(root.right, key);
        return root;
    }

    if (root.val !== key) {
        throw new Error('incommensurable keys');
    }

    // If it has at most one child, just replace it with its child (or null).
    if (!root.right) return root.left;
    if (!root.left) return root.right;

    // Its right child has no left child, so attach its left child as the left
    // child of its right child.
    if (!root.right.left) {
        root.right.left = root.left;
        return root.right;
    }

    // Find the minimal node in its right subtree.
    let parent = root.right;
    let child = parent.left;
    while (child.left) {
        parent = child;
        child = child.left;
    }

    // Replace it with that minimal node. Very carefully.
    parent.left = child.right;
    child.right = root.right;
    child.left = root.left;
    return child;
}
