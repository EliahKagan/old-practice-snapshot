'use strict';

function main(next) {
    const a = next();
    const b = next();
    console.log(a + b);
}

function splitIntoValues(input) {
    return input.split(/\s+/u).
            filter(tok => tok).
            map(tok => Number.parseInt(tok, 10));
}

(function () {
    const reads = [];
    process.stdin.resume();
    process.stdin.setEncoding('utf-8');
    process.stdin.on('data', data => reads.push(data));
    process.stdin.on('end', () => {
        const values = splitIntoValues(reads.join(''));
        let index = 0;
        main(() => values[index++]);
    });
})();
