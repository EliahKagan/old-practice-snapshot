<Query Kind="FSharpProgram" />

open System

let getRecord (line:string) = line.Split ' ' |> Array.map float
let inv = (/) 1.
let put name value = sprintf "%-12s%g" name value |> Dump

printfn "Enter one or more numbers, separated by spaces."

let a = Console.ReadLine () |> getRecord
let n = a |> Array.length |> float
let avg s = (Seq.sum s) / n

a |> avg |> put "arithmetic"
(Array.reduce (*) a) ** (inv n) |> put "geometric"
a |> Seq.map inv |> avg |> inv |> put "harmonic"
