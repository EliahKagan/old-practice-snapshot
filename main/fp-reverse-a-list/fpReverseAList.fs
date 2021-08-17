open System

let rec getAll () =
    [ match Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let rec reverse list =
    [ match list with
        | x::xs -> yield! reverse xs; yield x
        | [] -> () ]

getAll () |> reverse |> List.iter (printfn "%d")
