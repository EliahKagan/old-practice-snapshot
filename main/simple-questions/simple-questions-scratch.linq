<Query Kind="FSharpExpression" />

let printC operator leftDomain rightDomain =
    let table =
        let row x = rightDomain |> List.map (operator x >> sprintf "%A")
        leftDomain |> List.map row
    
    table

printC (-) [1..12] [1..12]