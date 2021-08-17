<Query Kind="FSharpProgram" />

open System
let rotate c = (int c - int '0' + 1) % 10 + int '0' |> char
Console.ReadLine () |> Seq.map rotate |> Seq.toArray |> Console.WriteLine
