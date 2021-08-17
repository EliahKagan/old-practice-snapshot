<Query Kind="FSharpExpression" />

let jugglerSequence =
    let rec build xs = function
    | 1L    ->
        1L::xs
    | x     ->
        float x ** (if x % 2L = 0L then 0.5 else 1.5) |> int64 |> build (x::xs)
    
    build [] >> List.rev

jugglerSequence 37L