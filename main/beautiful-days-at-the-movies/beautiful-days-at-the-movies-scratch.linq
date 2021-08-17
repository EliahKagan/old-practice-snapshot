<Query Kind="FSharpProgram" />

[<Literal>]
let numbase = 10

let reverse value =
    let rec rev acc = function
    | 0 -> acc
    | n -> rev (acc * numbase + n % numbase) (n / numbase)
    
    rev 0 value

reverse 50006 |> printfn "%d"