<Query Kind="FSharpProgram" />

let f = function
    | x::xs ->  printfn "%d   %A" x xs
    | []    ->  printfn "none"

f [10;20;30;40;50;60]

let g = function
    | (i, j)::xs ->  printfn "%d %d   %A" i j xs
    | []         ->  printfn "none"

g [(10, 20);(30, 40);(50, 60)]

assert (2 < 3)

abs -2 |> printfn "%d"

printfn ""
{0..10} |> Seq.filter (fun x -> x % 3 = 0) |> printfn "%A"
