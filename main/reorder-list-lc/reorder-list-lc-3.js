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
    if (!head) return null;
    
    const second = reverse(split(head));
    return interleave(head, second);
}

function split(head) {
    for (let fast = head; fast.next && fast.next.next; fast = fast.next.next) {
        head = head.next;
    }
    
    const second = head.next;
    head.next = null;
    return second;
}

function reverse(head) {
    let acc = null;
    
    while (head) {
        const next = head.next;
        head.next = acc;
        acc = head;
        head = next;
    }
    
    return acc;
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

function* emit_interleaved(first, second) {
    while (first && second) {
        yield first;
        first = first.next;
        
        yield second;
        second = second.next;
    }
    
    for (; first; first = first.next) {
        yield first;
    }
    
    for (; second; second = second.next) {
        yield second;
    }
}

function interleave(first, second) {
    return attach_in_order(emit_interleaved(first, second));
}
