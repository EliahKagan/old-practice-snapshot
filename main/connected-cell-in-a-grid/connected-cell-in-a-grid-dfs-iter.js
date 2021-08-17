'use strict';

function readGrid(next) {
    const height = next();
    const width = next();
    
    const grid = new Array(height);
    for (let i = 0; i < height; ++i) {
        grid[i] = new Array(width);
        for (let j = 0; j < width; ++j) {
            grid[i][j] = next() !== 0;
        }
    }
    
    return grid;
}

function height(grid) {
    return grid.length;
}

function width(grid) {
    return grid.length === 0 ? 0 : grid[0].length;
}

function computeMaxRegionSize(grid) { // Mutates grid.
    function exists(i, j) {
        return 0 <= i && i < height(grid) && 0 <= j && j < width(grid);
    }
    
    const stack = [];
    
    function fill(i, j) { // Returns the number of cells filled.
        let area = 0;
        stack.push([i, j]);
        
        while (stack.length !== 0) {
            [i, j] = stack.pop();
            if (!exists(i, j) || !grid[i][j]) continue;
            
            grid[i][j] = false;
            ++area;
            
            for (let h = i - 1; h <= i + 1; ++h) {
                for (let k = j - 1; k <= j + 1; ++k) {
                    stack.push([h, k]);
                }
            }
        }
        
        return area;
    }
    
    let max = 0;
    for (let i = 0; i < height(grid); ++i) {
        for (let j = 0; j < width(grid); ++j) {
            max = Math.max(max, fill(i, j));
        }
    }
    
    return max;
}

function main(next) {
    console.log(computeMaxRegionSize(readGrid(next)));
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
