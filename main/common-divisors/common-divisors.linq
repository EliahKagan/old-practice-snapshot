<Query Kind="FSharpProgram" />

open System

let inline bi b = if b then 1 else 0
let inline div p q = q % p = 0

let factor a b i = if div i a then bi (div i b) + bi (div (a / i) b) else 0

let split (s:string) = s.Split ' '

for t = 1 to Console.ReadLine () |> int do
    let a,b = match Console.ReadLine () |> split |> Array.map int with
                | [|x;y|] -> if x < y then x,y else y,x  // so a <= b
                | _ -> failwith "wrong number of fields in record"
    
    let n = a |> float |> sqrt |> ceil |> int
    
    Seq.sumBy (factor a b) {1 .. n - 1} + bi (n * n = a && div n b)
        |> printfn "%d"
