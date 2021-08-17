'use strict';

const BigNumber = require('bignumber.js');

function fibonacciModified(a, b, n) {
    for (let i = 2; i < n; ++i) {
        [a, b] = [b, b.pow(2).plus(a)];
    }
    
    return b;
}

function main(next) {
    const a = new BigNumber(next());
    const b = new BigNumber(next());
    const n = Number.parseInt(next());
    console.log(fibonacciModified(a, b, n).toFixed());
}

(function () {
    const reads = [];
    process.stdin.resume();
    process.stdin.setEncoding('utf-8');
    process.stdin.on('data', data => reads.push(data));
    process.stdin.on('end', () => {
        const tokens = reads.join('').trim().split(/\s+/u);
        let index = 0;
        main(() => tokens[index++]);
    });
})();
