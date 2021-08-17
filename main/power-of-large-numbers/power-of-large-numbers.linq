<Query Kind="FSharpProgram" />

[<Literal>]
let m = 1000000007L

let rec (^^) b e =
    if e < 2I then
        if e = 1I then b else 1L
    else
        let r = b ^^ (e / 2I)
        let s = r * r % m
        if e % 2I = 0I then s else s * b % m

let bigm = bigint m

let calculatePrice (ab : bigint array) =
    (ab.[0] % bigm |> int64) ^^ ab.[1]

let getln = System.Console.ReadLine

{1..(getln () |> int)}
|> Seq.iter (ignore >> getln
                    >> (fun s -> s.Split ' ')
                    >> Array.map System.Numerics.BigInteger.Parse
                    >> calculatePrice
                    >> printfn "%d")