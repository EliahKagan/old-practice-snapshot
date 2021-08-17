<Query Kind="FSharpProgram" />

let getSingle = System.Console.ReadLine >> int
let getFirst _ = ((System.Console.ReadLine ()).Split ' ').[0] |> int

for i = 1 to getSingle () |> int do
    // by problem constraints, (x, y) are unique, so just check if any x recurs
    let preimages = [1 .. getSingle ()] |> List.map getFirst
    (if preimages = List.distinct preimages then "YES" else "NO") |> printfn "%s"
