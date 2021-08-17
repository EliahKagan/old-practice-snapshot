function processData(input) {
    let [nk, toys] = input.split("\n").map(s => s.split(" ").map(Number));
    toys.sort((x, y) => x - y);
    let k = nk[1];
    
    let count = 0;
    for (let t of toys) {
        if ((k -= t) < 0) break;
        ++count;
    }
    
    console.log(count);
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
