<Query Kind="FSharpProgram" />

open System

let permute =
    let rec revBy2 acc = function
        | [] | [_] -> acc
        | y::x::xs -> revBy2 (y::x::acc) xs
    
    revBy2 [] >> List.rev

for i = 1 to Console.ReadLine () |> int do
    let s = Console.ReadLine ()
    s |> Seq.toList |> permute |> List.toArray |> Console.WriteLine
