<Query Kind="FSharpProgram" />

let get = System.Console.ReadLine >> (fun s -> s.Split ' ') >> Array.map int

let d = (get ()).[1] // n, d
let a = get ()

Array.append a.[d..] a.[..(d - 1)]
|> Seq.map string
|> String.concat " "
|> printfn "%s"
