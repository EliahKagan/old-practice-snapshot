<Query Kind="FSharpProgram" />

open System

let pent n = n * (n * 3L - 1L) / 2L

for t = 1 to Console.ReadLine () |> int do
    Console.ReadLine () |> int64 |> pent |> printfn "%d"
