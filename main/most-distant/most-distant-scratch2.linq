<Query Kind="FSharpProgram" />

open System

let inline coords () = (Console.ReadLine ()).Split ' '
let inline xcoord a = a.[0] |> int
let inline ycoord a = a.[1] |> int

let mutable xmin = Int32.MaxValue
let mutable xmax = Int32.MinValue
let mutable ymin = Int32.MaxValue
let mutable ymax = Int32.MinValue

n = Console.ReadLine () |> int

while (xmax < xmin || ymax < ymin) && n > 0 do
    let a = coords ()
    let x = xcoord a
    if x != 0 then
        if x < xmin then xmin <- x
        if x > xmax then xmax <- x