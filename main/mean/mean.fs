open System

let getRecord (line:string) = line.Split ' ' |> Array.map float
let inv = (/) 1.
let put = printfn "%-12s%g"

printfn "Enter one or more numbers, separated by spaces."
printf "> "

let a = Console.ReadLine () |> getRecord
let n = a |> Array.length |> float
let avg s = (Seq.sum s) / n

a |> avg |> put "arithmetic"
(Array.reduce (*) a) ** (inv n) |> put "geometric"
a |> Seq.map inv |> avg |> inv |> put "harmonic"
