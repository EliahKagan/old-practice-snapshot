let rec getAll () =
    [ match System.Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let rec length = function
    | x::xs -> length xs + 1
    | [] -> 0

getAll () |> length |> printfn "%d"
