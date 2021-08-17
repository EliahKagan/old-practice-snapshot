<Query Kind="FSharpProgram" />

open System

let n = Console.ReadLine () |> int

let row () =
    let line = Console.ReadLine ()
    line.Split ' ' |> Array.map int

let tally i (a:int[]) = a.[i] - a.[n - i - 1]

let tallyRow i = row () |> tally i

[0 .. n - 1] |> List.map tallyRow |> List.sum |> abs |> printfn "%d"
