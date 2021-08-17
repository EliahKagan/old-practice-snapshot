<Query Kind="FSharpProgram" />

let getLine = System.Console.ReadLine
let getRecord () = getLine () |> (fun s -> let a = s.Split ' ' in a.[0], a.[1])

let map = () |> List.replicate (getLine () |> int) |> Seq.map getRecord |> Map

let lookup key =
    match Map.tryFind key map with
    | None -> "Not found"
    | Some(value) -> key + "=" + value

let rec processQueries () =
    match getLine () with
    | null -> ()
    | name ->
        lookup name |> System.Console.WriteLine
        processQueries ()

processQueries ()
