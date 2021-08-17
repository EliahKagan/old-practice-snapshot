<Query Kind="FSharpProgram" />

open System

for i = 1 to Console.ReadLine () |> int do
    let s = Console.ReadLine ()
    let a = s.Split ' '
    bigint.Parse a.[0] * bigint.Parse a.[1] |> Console.WriteLine
