open System

let rec permute items =
    [ match items with
        | y::x::xs -> yield x; yield y; yield! permute xs
        | _ -> () ]

for i in [1 .. Console.ReadLine () |> int] do
    let str = Console.ReadLine ()
    str |> Seq.toList |> permute |> String.Concat |> printfn "%s"
