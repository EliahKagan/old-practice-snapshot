'use strict';

class Heap {
    constructor(compare) {
        this._elems = [];

        this._ok = function(parent, child) {
            return compare(this._elems[parent], this._elems[child]) <= 0;
        };
    }

    get length() {
        return this._elems.length;
    }

    peek() {
        if (this.length === 0) {
            throw new Error("can't peek into empty heap");
        }

        return this._elems[0];
    }

    push(value) {
        this._elems.push(value);
        this._siftUp(this.length - 1);
    }

    pop() {
        if (this.length === 0) {
            throw new Error("can't pop from empty heap");
        }

        const ret = this._elems[0];

        if (this.length === 1) {
            this._elems.length = 0;
        } else {
            this._elems[0] = this._elems.pop();
            this._siftDown(0);
        }

        return ret;
    }

    _siftUp(child) {
        while (child !== 0) {
            const parent = Math.trunc((child - 1) / 2);
            if (this._ok(parent, child)) break;

            this._swap(parent, child);
            child = parent;
        }
    }

    _siftDown(parent) {
        for (; ; ) {
            const child = this._pickChild(parent);
            if (child === undefined || this._ok(parent, child)) break;

            this._swap(parent, child);
            parent = child;
        }
    }

    _pickChild(parent) {
        const left = parent * 2 + 1;
        if (left >= this.length) return undefined;

        const right = left + 1;
        return right === this.length || this._ok(left, right) ? left : right;
    }

    _swap(parent, child) {
        [this._elems[parent], this._elems[child]] =
                [this._elems[child], this._elems[parent]];
    }
}

class MinHeap extends Heap {
    constructor() {
        super((lhs, rhs) => lhs - rhs);
    }
}

class MaxHeap extends Heap {
    constructor() {
        super((lhs, rhs) => rhs - lhs);
    }
}

class GrowingMedianBag {
    constructor() {
        this._low = new MaxHeap();
        this._high = new MinHeap();
    }

    get length() {
        return this._low.length + this._high.length;
    }

    push(value) {
        if (this._high.length === 0 || value <= this._high.peek()) {
            this._low.push(value);
        } else {
            this._high.push(value);
        }

        this._rebalance();
    }

    median() {
        switch (this._imbalance) {
        case -1:
            return this._high.peek();

        case +1:
            return this._low.peek();

        case 0:
            if (this.length === 0) {
                throw new Error("can't compute median of no values");
            }

            return (this._low.peek() + this._high.peek()) / 2;

        default:
            throw new Error('balancing invariant unexpectedly violated!');
        }
    }

    _rebalance() {
        switch (this._imbalance) {
        case -2:
            this._low.push(this._high.pop());
            break;

        case +2:
            this._high.push(this._low.pop());
            break;

        default:
            // The heaps cannot be made any more balanced.
        }
    }

    get _imbalance() {
        return this._low.length - this._high.length;
    }
}

function main(next) {
    const bag = new GrowingMedianBag();

    for (let queryCount = next(); queryCount > 0; --queryCount) {
        bag.push(next());
        console.log(bag.median().toFixed(1));
    }
}

(function () {
    const reads = [];
    process.stdin.resume();
    process.stdin.setEncoding('utf-8');
    process.stdin.on('data', data => reads.push(data));
    process.stdin.on('end', () => {
        const values = reads.join('')
                            .split(/\s+/u)
                            .map(tok => Number.parseInt(tok));
        let index = 0;
        main(() => values[index++]);
    });
})();
