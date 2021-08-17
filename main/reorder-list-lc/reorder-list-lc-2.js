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

function length(head) {
    let acc = 0;
    for (; head; head = head.next) {
        ++acc;
    }
    return acc;
}

function advance(head, distance) {
    for (; distance > 0; --distance) {
        if (!head) {
            throw new Error("can't advance past the last node");
        }
        head = head.next;
    }
    return head;
}

function split(head) {
    const middle = advance(head, Math.floor(length(head) / 2));
    const second = middle.next;
    middle.next = null;
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