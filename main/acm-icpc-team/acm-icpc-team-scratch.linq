<Query Kind="FSharpProgram" />

open System
open System.Collections

let m = Console.ReadLine () |> int

let asBits (s:string) =
    let bits = BitArray m
    
    for i = 1 to m do
        if s.[i] <> '0' then bits.[i] <- true
    
    bits