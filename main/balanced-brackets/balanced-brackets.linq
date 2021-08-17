<Query Kind="FSharpProgram" />

let balanced text =
    let rec bal closers = function
    | [] -> List.isEmpty closers
    | ch::chs ->
        match ch with
        | '('               -> bal (')'::closers) chs
        | '['               -> bal (']'::closers) chs
        | '{'               -> bal ('}'::closers) chs
        | ')' | ']' | '}'   ->
            match closers with
            | x::xs when x = ch     -> bal xs chs
            | _                     -> false
        | _                 -> bal closers chs
    
    text |> Seq.toList |> bal []

let yesNo = function
| true  -> "YES"
| false -> "NO"

let getln = System.Console.ReadLine

{1..(getln () |> int)}
|> Seq.iter (ignore >> getln >> balanced >> yesNo >> printfn "%s")