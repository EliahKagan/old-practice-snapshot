function processData(input) {
    const s = "\u2571\u2572".repeat(7);
    for (let i = 14; i !== 0; --i) console.log(s);
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
