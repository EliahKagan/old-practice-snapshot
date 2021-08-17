let rec getAll () =
    [ match System.Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let length =
    let rec len n list =
        match list with
            | [] -> n
            | x::xs -> len (n + 1) xs
    
    len 0

getAll () |> length |> printfn "%d"
