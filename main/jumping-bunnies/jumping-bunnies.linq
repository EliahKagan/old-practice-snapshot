<Query Kind="FSharpProgram" />

let rec gcd m n =
    match n with
    | 0L -> m
    | _ -> m % n |> gcd n

let lcm m n = m / gcd m n * n

let getln = System.Console.ReadLine

getln () |> ignore // don't need "number of bunnies"

getln ()
|> (fun s -> s.Split ' ')
|> Seq.map int64
|> Seq.reduce lcm
|> printfn "%d"