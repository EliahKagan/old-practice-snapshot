let rec getAll () =
    [ match System.Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let length = List.map (fun x -> 1) >> List.sum

getAll () |> length |> printfn "%d"
