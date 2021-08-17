<Query Kind="FSharpProgram" />

open Checked

match stdin.ReadLine () |> Int64.TryParse with
| true,  n  ->
    try
        n * n |> printfn "%d squared is %d." n
    with
    | :? OverflowException as e -> eprintfn "error: %s" e.Message
| false, _  ->
    eprintfn "error: Input must be an integer from %d to %d."
             Int64.MinValue Int64.MaxValue