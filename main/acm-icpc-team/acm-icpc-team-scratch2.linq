<Query Kind="FSharpProgram" />

open System
open System.Collections

let n, m =
    let nm = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int
    nm.[0], nm.[1]

let asBits (s:string) =
    let bits = BitArray m
    
    for i = 1 to m do
        if s.[i] <> '0' then bits.[i] <- true
    
    bits

let a = Array.init n (fun _ -> Console.ReadLine () |> asBits)

let mutable topics, teams = 0, 0

for i = 0 to n - 2 do
    for j = i + 1 to n - 1 do
        a.[i].Or a.[j]