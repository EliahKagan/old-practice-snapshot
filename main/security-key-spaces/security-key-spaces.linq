<Query Kind="FSharpProgram" />

open System

let s = Console.ReadLine ()
let e = Console.ReadLine () |> int

let rotate c = (int c - int '0' + e) % 10 + int '0' |> char
s |> Seq.map rotate |> Seq.toArray |> Console.WriteLine
