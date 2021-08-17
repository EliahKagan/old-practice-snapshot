function processData(a) {
    var max = Number.MIN_SAFE_INTEGER, ans = Number.MIN_SAFE_INTEGER;
    
    for (var x of a) {
        if (x <= ans || x === max) continue;
        
        if (x > max) {
            ans = max;
            max = x;
        }
        else ans = x;
    }
    
    console.log(ans);
}


// tail starts here
process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input.split('\n')[1].split(' ').map(Number));
});
