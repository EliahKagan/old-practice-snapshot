<Query Kind="FSharpProgram" />

open System

let inline bi b = if b then 1 else 0
let inline div p q = q % p = 0
let getln = Console.ReadLine

let a,b = match getln () |> (fun s -> s.Split ' ') |> Array.map int with
            | [|x;y|] -> if x < y then x,y else y,x  // so a < b
            | _ -> failwith "wrong number of fields in record"

let n = a |> float |> sqrt |> ceil |> Convert.ToInt32

{1 .. n - 1} |> Seq.sumBy ((fun i -> div i a && div i b) >> bi)
             |> (+) (n * n = a |> bi) |> (+) ((div a b && a <> 1) |> bi)
             |> printfn "%d"
