<Query Kind="FSharpProgram" />

open System

let rec gcd m = function
    | 0L -> m
    | n -> m % n |> gcd n

for t = 1 to Console.ReadLine () |> int do
    let abxy = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int64
    let reachable = gcd abxy.[0] abxy.[1] = gcd abxy.[2] abxy.[3]
    (if reachable then "YES" else "NO") |> Console.WriteLine
