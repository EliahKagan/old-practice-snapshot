'use strict';

const NOT_FOUND = -1;

// A node in a circular doubly linked list.
function Node(prev, key, value) {
    this.key = key;
    this.value = value;

    if (prev) {
        // This is a non-sentinel node, inserted into an existing chain.
        this.attach(prev);
    } else {
        // This is a sentinel node.
        this.prev = this.next = this;
    }
}

Node.prototype.attach = function(prev) {
    this.prev = prev;
    this.next = prev.next;

    prev.next.prev = this;
    prev.next = this;
};

Node.prototype.detach = function() {
    this.prev.next = this.next;
    this.next.prev = this.prev;
};

/**
 * @param {number} capacity
 */
function LRUCache(capacity) {
    if (!Number.isInteger(capacity) || capacity <= 0) {
        throw new RangeError('capacity must be a positive integer');
    }

    this._capacity = capacity;
    this._length = 0;
    this._chain = new Node(); // Sentinel node.
    this._map = {};
}

/**
 * @param {number} key
 * @return {number}
 */
LRUCache.prototype.get = function(key) {
    const node = this._map[key];

    if (node) {
        this._bump(node);
        return node.value;
    }

    return NOT_FOUND;
};

/**
 * @param {number} key
 * @param {number} value
 * @return {void}
 */
LRUCache.prototype.put = function(key, value) {
    let node = this._map[key];

    if (node) {
        this._bump(node);
        node.value = value;
        return;
    }

    if (this._length < this._capacity) {
        ++this._length;
        node = new Node(this._chain, key, value);
    } else {
        node = this._chain.prev;
        this._bump(node);

        delete this._map[node.key];
        node.key = key;
        node.value = value;
    }

    this._map[key] = node;
};

LRUCache.prototype._bump = function(node) {
    node.detach();
    node.attach(this._chain);
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * var obj = new LRUCache(capacity)
 * var param_1 = obj.get(key)
 * obj.put(key,value)
 */