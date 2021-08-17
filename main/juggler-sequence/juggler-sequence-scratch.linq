<Query Kind="FSharpProgram" />

open Checked

let jugglerSequence =
    let rec build xs = function
    | 1L    ->
        1L::xs
    | x     ->
        float x ** (if x % 2L = 0L then 0.5 else 1.5) |> int64 |> build (x::xs)
    
    build [] >> List.rev

let jugglers = [1L..100L] |> List.map jugglerSequence

jugglers |> List.map List.max |> Dump |> List.max |> printfn "%d"
jugglers |> List.map List.length |> Dump |> List.max |> printfn "%d"