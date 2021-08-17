let getval () = System.Console.ReadLine() |> int

[<EntryPoint>]
let main argv =
    getval () + getval () |> printfn "%d"
    0
