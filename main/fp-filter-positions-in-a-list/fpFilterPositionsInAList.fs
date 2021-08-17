open System

let rec getAll () =
    [ match Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let rec everyOther list =
    [ match list with
        | _::x::xs -> yield x; yield! everyOther xs
        | _ -> () ]

getAll () |> everyOther |> List.iter (printfn "%d")
