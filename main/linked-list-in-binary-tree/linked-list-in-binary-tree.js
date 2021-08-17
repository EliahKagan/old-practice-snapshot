/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */
/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */

function isSubPathAt(head, root) {
    if (!head) return true;
    
    if (!root || head.val !== root.val) return false;
    
    return isSubPathAt(head.next, root.left) ||
            isSubPathAt(head.next, root.right);
}

function hasNonemptySubPath(head, root) {
    if (!root) return false;
    
    return isSubPathAt(head, root) ||
            hasNonemptySubPath(head, root.left) ||
            hasNonemptySubPath(head, root.right);
}

/**
 * @param {ListNode} head
 * @param {TreeNode} root
 * @return {boolean}
 */
function isSubPath(head, root) {
    return !head || hasNonemptySubPath(head, root);
}
