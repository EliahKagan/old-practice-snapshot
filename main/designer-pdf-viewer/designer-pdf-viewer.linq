<Query Kind="FSharpProgram" />

let h = stdin.ReadLine().Split ' ' |> Array.map int
let word = stdin.ReadLine().Trim ()

let height =
    let a = int 'a'
    word |> Seq.map (fun c -> h.[int c - a]) |> Seq.max
    
height * String.length word |> printfn "%d"