<Query Kind="FSharpExpression" />

try
    stdin.ReadLine () |> float |> (fun n -> n * n) |> printfn "%g"
    0
with
| :? OverflowException
| :? FormatException ->
    eprintfn "error: non-numeric input cannot be squared"
    1