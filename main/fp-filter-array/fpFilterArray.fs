open System

let rec getAll () =
    [ match Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let rec filter pred list =
    [ match list with
        | [] -> ()
        | x::xs ->
            if pred x then yield x
            yield! filter pred xs ]

let bound = Console.ReadLine () |> int
getAll () |> filter ((>) bound) |> List.iter (printfn "%d")
