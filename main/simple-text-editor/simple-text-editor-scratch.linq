<Query Kind="FSharpProgram" />

[<Literal>]
let Append = 1

[<Literal>]
let Erase = 2

[<Literal>]
let Print = 3

[<Literal>]
let Undo = 4

let query = 2

let interpret = function
| Append    -> "add text to the end"
| Erase     -> "remove text from the end"
| Print     -> "show part of the text"
| Undo      -> "put the text back the way it was"
| _         -> failwith "unrecognized query type"

interpret query |> printfn "%s"