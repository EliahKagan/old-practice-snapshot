/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */
/**
 * @param {ListNode} head
 * @return {void} Do not return anything, modify head in-place instead.
 */
function reorderList(head) {
    return attach_in_order(outside_in(head));
}

function attach_in_order(nodes) {
    const sentinel = new ListNode(undefined);
    let current = sentinel;

    for (const node of nodes) {
        current.next = node;
        current = node;
    }

    current.next = null;
    return sentinel.next;
}

function* outside_in(head) {
    const nodes = get_nodes(head);

    let left = 0;
    let right = nodes.length - 1;

    while (left < right) {
        yield nodes[left++];
        yield nodes[right--];
    }

    if (left === right) {
        yield nodes[left];
    }
}

function get_nodes(head) {
    const nodes = [];

    for (; head; head = head.next) {
        nodes.push(head);
    }

    return nodes;
}
