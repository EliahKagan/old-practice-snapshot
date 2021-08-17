'use strict';

function splitIntoLines(input) {
    return input.split('\n')
                .map(line => line.trim())
                .filter(line => line);
}

function splitIntoValues(line) {
    return line.split(/\s+/u)
               .filter(tok => tok)
               .map(tok => Number.parseInt(tok));
}

function asValue(line) {
    return Number.parseInt(line);
}

const BLOCKED_CELL = 'X'; // Must be this character.
const END_CELL = '*'; // Must be this character.
const CLEARED_CELL = '#'; // Can be anything but BLOCKED_CELL and END_CELL.

const NO_PATH = undefined;

class Board {
    constructor(nextLine) {
        [this._height, this._width] = splitIntoValues(nextLine());
        this._cells = new Array(this._height);

        for (let i = 0; i < this._height; ++i) {
            const line = nextLine();
            if (line.length !== this._width) {
                throw new Error('wrong-width row');
            }

            const jStart = line.indexOf('M');
            if (jStart >= 0) {
                this._iStart = i;
                this._jStart = jStart;
            }

            this._cells[i] = line.split('');
        }

        if (this._iStart === undefined || this._jStart === undefined) {
            throw new Error('start location not found');
        }
    }

    countChoices() {
        if (this._canGo(this._iStart, this._jStart)) {
            return this._dfs(this._iStart, this._jStart);
        }

        return NO_PATH;
    }

    _dfs(i, j) {
        if (this._cells[i][j] === END_CELL) {
            return 0;
        }

        const nei = [[i, j - 1],
                     [i, j + 1],
                     [i - 1, j],
                     [i + 1, j]].filter(coords => this._canGo(...coords));

        this._cells[i][j] = BLOCKED_CELL;

        let count = NO_PATH;

        for (const coords of nei) {
            count = this._dfs(...coords);
            if (count !== NO_PATH) break;
        }

        this._cells[i][j] = CLEARED_CELL;

        return count !== NO_PATH && nei.length > 1 ? count + 1 : count;
    }

    _canGo(i, j) {
        return this._exists(i, j) && this._cells[i][j] !== BLOCKED_CELL;
    }

    _exists(i, j) {
        return 0 <= i && i < this._height && 0 <= j && j < this._width;
    }
}

function main(nextLine) {
    for (let t = asValue(nextLine()); t > 0; --t) {
        const board = new Board(nextLine);
        const guess = asValue(nextLine());

        const count = board.countChoices();
        if (count === NO_PATH) {
            throw new Error('no path out of the forest');
        }

        console.log(guess === count ? 'Impressed' : 'Oops!');
    }
}

(function () {
    const reads = [];
    process.stdin.resume();
    process.stdin.setEncoding('utf-8');
    process.stdin.on('data', data => reads.push(data));
    process.stdin.on('end', () => {
        const lines = splitIntoLines(reads.join(''));
        let index = 0;
        main(() => lines[index++]);
    });
})();
