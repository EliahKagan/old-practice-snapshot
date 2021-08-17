<Query Kind="FSharpProgram" />

[<Literal>]
let numbase = 10

let reverse value =
    let rec rev acc = function
    | 0 -> acc
    | n -> rev (acc * numbase + n % numbase) (n / numbase)
    
    rev 0 value

let i, j, k =
    System.Console.ReadLine ()
    |> (fun s -> s.Split ' ')
    |> Array.map int
    |> (fun a -> a.[0], a.[1], a.[2])

{i..j}
|> Seq.filter (fun x -> (x - reverse x) % k = 0)
|> Seq.length
|> printfn "%d"