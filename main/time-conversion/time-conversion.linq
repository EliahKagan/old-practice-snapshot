<Query Kind="FSharpProgram" />

open System
let time = Console.ReadLine () |> DateTime.Parse
time.ToString "HH:mm:ss" |> printfn "%s"
