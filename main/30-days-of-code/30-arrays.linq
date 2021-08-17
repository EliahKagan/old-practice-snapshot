<Query Kind="FSharpProgram" />

let n, a =
    let getln = System.Console.ReadLine
    getln () |> int, getln () |> (fun s -> s.Split ' ')

if (Array.length a <> n) then failwith "input record not of specified length"

a |> Array.rev |> String.concat " " |> printfn "%s"
