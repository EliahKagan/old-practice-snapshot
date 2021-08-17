<Query Kind="FSharpProgram" />

let rec reverse list =
    [ match list with
        | x::xs -> yield! reverse xs; yield x
        | [] -> () ]

[1..10] |> reverse |> printfn "%A"
[3] |> reverse |> printfn "%A"
[] |> reverse |> printfn "%A"