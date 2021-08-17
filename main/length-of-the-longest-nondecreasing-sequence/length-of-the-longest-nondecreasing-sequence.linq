<Query Kind="FSharpProgram" />

open System
open System.Text.RegularExpressions

let maxNondecreasingWindowSize =
    let rec lengths acc n prev = function
    | x::xs when prev <= x  -> lengths acc (n + 1) x xs
    | x::xs                 -> lengths (n::acc) 1 x xs
    | []                    -> n::acc
    
    lengths [] 0 Int32.MinValue >> List.max

Regex.Split (Console.In.ReadToEnd().Trim(), @"\s+")
|> Seq.skip 1
|> Seq.map int
|> Seq.toList
|> maxNondecreasingWindowSize
|> printfn "%d"