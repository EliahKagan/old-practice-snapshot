open System

let rec getAll () =
    [ match Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let sumOdds = List.filter (fun i -> i % 2 <> 0) >> List.sum

getAll () |> sumOdds |> printfn "%d"
