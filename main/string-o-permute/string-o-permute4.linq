<Query Kind="FSharpProgram" />

open System

// attempt to improve performance with incomplete pattern match
let rec permute = function
    | [] -> []
    | y::x::xs -> x::y::(permute xs)

for i = 1 to Console.ReadLine () |> int do
    let s = Console.ReadLine ()
    s |> Seq.toList |> permute |> List.toArray |> Console.WriteLine
