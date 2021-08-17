<Query Kind="FSharpProgram" />

let reverse values =
    let rec rev xs acc =
        match xs with
        | x::xs' -> x::acc |> rev xs'
        | []     -> acc
    
    rev values []

reverse [10; 20; 30; 40; 50; 60; 70] |> printfn "%A"
