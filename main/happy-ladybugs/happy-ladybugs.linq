<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine
let ignoreln = getln >> ignore // don't need n
let getboard = ignoreln >> getln >> Seq.toList

let rec won = function
| []                                -> true
| '_'::xs                           -> won xs
| z::y::x::xs  when z = y && y = x  -> y::x::xs |> won
| y::x::xs     when y = x           -> won xs
| _                                 -> false

let winnable board =
    board |> (if List.contains '_' board then List.sort else id) |> won

let yesno b = if b then "YES" else "NO"

let g = getln () |> int
{1..g} |> Seq.iter (ignore >> getboard >> winnable >> yesno >> printfn "%s")