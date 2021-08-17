<Query Kind="FSharpProgram" />

open System

let xs =
    let n = Console.ReadLine () |> int
    let s = Console.ReadLine ()
    let a = s.Split ' '
    Seq.take (min n a.Length) a |> Seq.map int

xs |> Seq.sum |> printfn "%d"
