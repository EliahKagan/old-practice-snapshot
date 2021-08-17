<Query Kind="FSharpProgram" />

let dsum: string->int64 =
    let z = int64 '0'
    Seq.sumBy (fun c -> int64 c - z)

let rec super s =
    if String.length s = 1 then s else s |> dsum |> string |> super

let nk = System.Console.ReadLine () |> (fun s -> s.Split ' ')
dsum nk.[0] * int64 nk.[1] |> string |> super |> printfn "%s"
