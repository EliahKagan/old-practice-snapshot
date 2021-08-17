<Query Kind="FSharpProgram" />

let a = System.Console.ReadLine().Split ' ' |> Array.map int64
let sum = Array.sum a
printfn "%d %d" (sum - Array.max a) (sum - Array.min a)