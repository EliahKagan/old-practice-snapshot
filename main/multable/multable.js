/*
 * This is a JavaScript Scratchpad.
 *
 * Enter some JavaScript, then Right Click or choose from the Execute Menu:
 * 1. Run to evaluate the selected text (Ctrl+R),
 * 2. Inspect to bring up an Object Inspector on the result (Ctrl+I), or,
 * 3. Display to insert the result in a comment after the selection. (Ctrl+L)
 */

(function () {
    'use strict';
    
    function emit_table(low, high) {
        if (!Number.isInteger(low) || !Number.isInteger(high))
            throw new Error('interval bounds must be integers');
        
        if (high < low) throw new Error('interval must be nonempty');
        
        const width = String(high * high).length;
        
        for (let i = low; i <= high; ++i) {
            const tokens = [];
            for (let j = low; j <= high; ++j)
                tokens.push(String(i * j).padStart(width));
            console.log('', tokens.join(' '));
        }
    }
    
    emit_table(1, 12);
    console.log();
    emit_table(1, 33);
})();
