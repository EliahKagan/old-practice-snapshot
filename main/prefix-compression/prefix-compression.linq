<Query Kind="FSharpProgram" />

let x, y = let getln = System.Console.ReadLine in getln (), getln ()
let xlen, ylen = String.length x, String.length y
let minlen = min xlen ylen

let rec plen i = if i = minlen || x.[i] <> y.[i] then i else i + 1 |> plen
let p = plen 0

printfn "%d %s" p x.[0..(p - 1)]
printfn "%d %s" (xlen - p) x.[p..]
printfn "%d %s" (ylen - p) y.[p..]
