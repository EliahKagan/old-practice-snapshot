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

function isSubPathAfter(head, root) {
    for (const stack = [[head, root]]; stack.length !== 0; ) {
        [head, root] = stack.pop();
        if (!head.next) return true;
        
        if (root.right && head.next.val === root.right.val) {
            stack.push([head.next, root.right]);
        }
        
        if (root.left && head.next.val === root.left.val) {
            stack.push([head.next, root.left]);
        }
    }
    
    return false;
}

function hasNonemptySubPath(head, root) {
    for (const stack = [root]; stack.length !== 0; ) {
        root = stack.pop();
        
        if (head.val === root.val && isSubPathAfter(head, root)) {
            return true;
        }
        
        if (root.right) {
            stack.push(root.right);
        }
        
        if (root.left) {
            stack.push(root.left);
        }
    }
    
    return false;
}

/**
 * @param {ListNode} head
 * @param {TreeNode} root
 * @return {boolean}
 */
function isSubPath(head, root) {
    return !head || (root && hasNonemptySubPath(head, root));
}
