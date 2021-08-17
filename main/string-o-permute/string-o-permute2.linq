<Query Kind="FSharpProgram" />

open System

let permute i = if i % 2 = 0 then i + 1 else i - 1
let permuteStr (s:string) i = s.[permute i]

for i = 1 to Console.ReadLine () |> int do
    let s = Console.ReadLine ()
    let n = String.length s
    [|0 .. n - 1|] |> Array.map (permuteStr s) |> Console.WriteLine
