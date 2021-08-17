let rec getAll () =
    [ match System.Console.ReadLine () with
        | null -> ()
        | line -> yield int line; yield! getAll () ]

let reverse =
    let rec rev acc = function
        | [] -> acc
        | x::xs -> rev (x::acc) xs
    
    rev []

getAll () |> reverse |> List.iter (printfn "%d")
