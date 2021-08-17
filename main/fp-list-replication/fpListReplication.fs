open System

let s = Console.ReadLine () |> int

let rec rep () =
    let x = Console.ReadLine ()
    if x = null then () else int x |> repPrint
and repPrint n = 
    for i = 1 to s do printfn "%d" n
    rep ()

rep ()
