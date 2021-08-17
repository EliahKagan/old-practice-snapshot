<Query Kind="FSharpProgram" />

open System

let fibonacci n =
    let m = 100000007

    let rec fib i acc =
        match i, acc with
        | 0, _ -> acc
        | i, b::a::xs -> (a + b) % m :: acc |> fib (i - 1)
        | _, _ -> failwith "need 2 numbers to start Fibonacci sequence"
    
    [1;0] |> fib (n - 2 |> max 0) |> List.toArray |> Array.rev

let indices =
    let get = Console.ReadLine >> int
    Array.replicate (get ()) () |> Array.map get

let sequence = Array.max indices + 1 |> fibonacci

indices |> Array.iter (fun i -> sequence.[i] |> printfn "%d")
