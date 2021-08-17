'use strict';

const BASE = 10, HIGH_MULTIPLIER = 2**32;

function Int64(digits) {
    let lo = 0, hi = 0;

    for (const c of digits) {
        lo = lo * BASE + Number(c);
        hi = hi * BASE + Math.floor(lo / HIGH_MULTIPLIER);
        lo %= HIGH_MULTIPLIER;
    }

    return { lo, hi };
}

function half(i64) {
    return {
        lo: Math.floor((i64.hi % 2 * HIGH_MULTIPLIER + i64.lo) / 2),
        hi: Math.floor(i64.hi / 2)
    }
}

const p = Int64('818638958430279427');
console.log(p, half(p));
