<Query Kind="FSharpProgram" />

// Prints a Cayley table for the specified operator, left operand domain,
// and right operand domain, Way C: inferring the appropriate column width.
let printC operator leftDomain rightDomain =
    let table =
        let row x = rightDomain |> List.map (operator x >> sprintf "%A")
        leftDomain |> List.map row
    
    let cell =
        let maxWidthInRow = Seq.map String.length >> Seq.max
        let width = table |> Seq.map maxWidthInRow |> Seq.max
        sprintf "%*s" width
    
    table
    |> List.map (List.map cell >> String.concat " ")
    |> String.concat System.Environment.NewLine
    |> printfn "%s"

printC ( ** ) [1I..8I] [1..8]