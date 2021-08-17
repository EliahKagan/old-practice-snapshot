<Query Kind="FSharpProgram" />

open System

let inline bi b = if b then 1 else 0
//let inline div p q = q % p = 0
let div p q = if  q % p = 0 then sprintf "%d divides %d." p q |> Dump; true else false
let getln = Console.ReadLine

let a,b = match getln () |> (fun s -> s.Split ' ') |> Array.map int with
            | [|x;y|] -> if x < y then x,y else y,x  // so a < b
            | _ -> failwith "wrong number of fields in record"

let n = a |> float |> sqrt |> ceil |> Convert.ToInt32
let factor i = if div i a then bi (div i b) + bi (div (a / i) b) else 0

Seq.sumBy factor {1 .. n - 1} + bi (n * n = a) |> printfn "%d"
