<Query Kind="FSharpProgram" />

open System

let yield2 a b = seq {yield a; yield b}
let id x = x

let p = Console.ReadLine ()
let q = Console.ReadLine ()

Seq.map2 yield2 p q |> Seq.collect id |> String.Concat |> printfn "%s"