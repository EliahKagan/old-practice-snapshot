<Query Kind="FSharpProgram" />

open Checked

let rec pown baseval = function
    | 0 ->
        1
    | exponent ->
        let r = exponent / 2 |> pown baseval
        let s = r * r
        if exponent % 2 = 0 then s else s * baseval

let countWays total exponent =
    let rec count subtot start =
        match subtot with
        | 0 ->
            1
        | _ ->
            let term = pown start exponent
            
            if term > subtot then
                0
            else
                count (subtot - term) (start + 1) + count subtot (start + 1)
    
    count total 1

let readValue = System.Console.ReadLine >> int
let total = readValue ()
let exponent = readValue ()
countWays total exponent |> printfn "%d"
