<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let n = getln () |> int

let a =
    let getxy = getln >> (fun s -> s.Split ' ') >> Array.map int
    Array.init n (ignore >> getxy)
 
let term i j = // term in shoelace formula due to ith and jth points in a
    let inline xcoord index = a.[index].[0]
    let inline ycoord index = a.[index].[1]
    let inline det x1 x2 y1 y2 = x1 * y2 - x2 * y1
    det (xcoord i) (xcoord j) (ycoord i) (ycoord j)

let sum = Seq.sumBy (fun i -> term i (i + 1)) {0 .. n - 2} + term (n - 1) 0
sum |> abs |> float |> (fun z -> z / 2.) |> printfn "%.1f"
