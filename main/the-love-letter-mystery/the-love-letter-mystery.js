function stepsToPalindrome(s) {
    const n = s.length - 1, h = Math.trunc(s.length / 2);
    
    let acc = 0;
    for (let i = 0; i !== h; ++i)
        acc += Math.abs(s.charCodeAt(i) - s.charCodeAt(n - i));
    
    return acc;
}

function processData(input) {
    let [_, ...lines] = input.split("\n");
    for (let s of lines.map(line => line.trim()))
        console.log(stepsToPalindrome(s));
} 

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input);
});
