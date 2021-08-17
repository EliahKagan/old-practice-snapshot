<Query Kind="FSharpProgram" />

let rec lines () =
    seq {
        match System.Console.ReadLine () with
        | null -> ()
        | line ->
            yield   line
            yield!  lines ()
    }

lines () |> Seq.length |> printfn "%d"