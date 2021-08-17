open System

let rec getAll () =
    [ match Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let rep n xs = List.collect (List.replicate n) xs

let s = Console.ReadLine () |> int
getAll () |> rep s |> List.iter (printfn "%d")
