<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let n = getln () |> int

let a =
    let getxy = getln >> (fun s -> s.Split ' ') >> Array.map int
    Array.init n (ignore >> getxy)

let dist i j =
    let inline xcoord index = a.[index].[0]
    let inline ycoord index = a.[index].[1]
    let inline sq z = z * z
    sq (xcoord i - xcoord j) + sq (ycoord i - ycoord j) |> float |> sqrt

Seq.sumBy (fun i -> dist i (i + 1)) {0 .. n - 2} + dist (n - 1) 0 |> printfn "%f"
