<Query Kind="FSharpProgram" />

let rec gcd m n = 
    match n with
        | 0 -> m
        | _ -> m % n |> gcd n

let ab =
    let line = System.Console.ReadLine ()
    line.Split ' ' |> Array.map int

gcd ab.[0] ab.[1] |> printfn "%d"