<Query Kind="FSharpProgram" />

open System

let inline coords () = (Console.ReadLine ()).Split ' '
let inline xcoord (xy:'a[]) = xy.[0] |> int
let inline ycoord (xy:'a[]) = xy.[1] |> int

let mutable xmin = Int32.MaxValue
let mutable xmax = Int32.MinValue
let mutable ymin = Int32.MaxValue
let mutable ymax = Int32.MinValue

let mutable xWas0 = false
let mutable yWas0 = false

let mutable n = Console.ReadLine () |> int

while not (xWas0 && yWas0) && n > 0 do
    let xy = coords ()
    
    let x = xcoord xy
    if x = 0 then xWas0 <- true
    if x < xmin then xmin <- x
    if x > xmax then xmax <- x
    
    let y = ycoord xy
    if y = 0 then yWas0 <- true
    if y < ymin then ymin <- y
    if y > ymax then ymax <- y
    
    n <- n - 1

while n > 0 do
    let xy = coords ()
    let x = xcoord xy
    if x <> 0 then
        if x < xmin then
            xmin <- x
        elif x > xmax then 
            xmax <- x
    else
        let y = ycoord xy
        if y < ymin then
            ymin <- y
        elif y > ymax then
            ymax <- y
    
    n <- n - 1

let distance =
    if xWas0 && yWas0 then
        let delta = max (xmax - xmin) (ymax - ymin) |> float
        
        let hypot =
            let a = max (abs xmin) (abs xmax) |> float
            let b = max (abs ymin) (abs ymax) |> float
            a * a + b * b |> sqrt
        
        max delta hypot
    else // problem constrains ensure xWas0 or yWas0, so here xWas0 iff yWas0
        (if yWas0 then xmax - xmin else ymax - ymin) |> float

Console.WriteLine distance
