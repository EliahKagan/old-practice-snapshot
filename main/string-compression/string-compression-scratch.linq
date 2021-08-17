<Query Kind="FSharpProgram" />

let addItem acc x =
    match acc with
    | (y, n)::pairs when y = x -> (x, n + 1)::pairs
    | pairs -> (x, 1)::pairs

let serialize = function
    | (x, 1) -> string x
    | (x, n) -> string x + string n

let s = "abbcdddeffghhhhijklmmnoppp"
s |> Seq.fold addItem [] |> List.map serialize |> List.rev |> String.concat ""
                                                           |> printfn "%s"
