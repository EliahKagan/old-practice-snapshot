<Query Kind="FSharpProgram" />

open System

let mutable xmax = 0
let mutable ymax = 0

for i = 1 to Console.ReadLine () |> int do
    let a = (Console.ReadLine ()).Split ' '
    let x = a.[0] |> int
    if x = 0 then
        let y = a.[1] |> int |> abs
        if ymax < y then ymax <- y
    else
        let x' = abs x
        if xmax < x' then xmax <- x'

let inline sq z = z * z
(xmax |> float |> sq) + (ymax |> float |> sq) |> sqrt |> printfn "%f"
