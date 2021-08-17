<Query Kind="FSharpProgram" />

open System
let n = Console.ReadLine () |> int
[1..n] |> List.iter (fun i -> String ('#', i) |> printfn "%*s" n)
