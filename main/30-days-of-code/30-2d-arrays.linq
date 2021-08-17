<Query Kind="FSharpProgram" />

let n = 6
let range = {1 .. n - 2}
let range2D = Seq.collect (fun i -> Seq.map (fun j -> i, j) range) range

let a =
    let getRow _ = System.Console.ReadLine () |> (fun s -> s.Split ' ')
    let rows = Array.init n getRow
    Array2D.init n n (fun i j -> rows.[i].[j] |> int)

let sumAt ij =
    let i, j = ij
    let above = a.[i - 1, j - 1] + a.[i - 1, j] + a.[i - 1, j + 1]
    let below = a.[i + 1, j - 1] + a.[i + 1, j] + a.[i + 1, j + 1]
    above + a.[i, j] + below

range2D |> Seq.map sumAt |> Seq.max |> printfn "%d"
