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

            const jEnd = line.indexOf('*');
            if (jEnd >= 0) {
                this._iEnd = i;
                this._jEnd = jEnd;
            }

            // True for blocked, false for unblocked - like a visitation list.
            this._cells[i] = line.split('').map(ch => ch === BLOCKED_CELL);
        }

        if (this._iStart === undefined || this._jStart === undefined) {
            throw new Error('start location not found');
        }

        if (this._iEnd === undefined || this._jEnd === undefined) {
            throw new Error('end location not found');
        }
    }

    countChoices() {
        if (this._canGo(this._iStart, this._jStart)) {
            return this._dfs(this._iStart, this._jStart);
        }

        return NO_PATH;
    }

    _dfs(i, j) {
        if (i === this._iEnd && j === this._jEnd) {
            return 0;
        }

        const nei = [[i, j - 1],
                     [i, j + 1],
                     [i - 1, j],
                     [i + 1, j]].filter(coords => this._canGo(...coords));

        this._cells[i][j] = true;

        let count = NO_PATH;

        for (const coords of nei) {
            count = this._dfs(...coords);
            if (count !== NO_PATH) break;
        }

        this._cells[i][j] = false;

        return count !== NO_PATH && nei.length > 1 ? count + 1 : count;
    }

    _canGo(i, j) {
        return this._exists(i, j) && !this._cells[i][j];
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
