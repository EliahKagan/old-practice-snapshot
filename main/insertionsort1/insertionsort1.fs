open System

let print = Array.map string >> String.concat " " >> printfn "%s"

let insertionSortLast a n =
    let mutable i = n - 1
    let e = a.[i]
    () // FIXME: implement the rest

let n = Console.ReadLine () |> int
let a = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int
Array.length a |> max n |> min 1 |> insertionSortLast a
