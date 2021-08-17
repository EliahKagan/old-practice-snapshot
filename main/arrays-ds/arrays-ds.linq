<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

getln ()

getln ()
|> (fun s -> s.Split ' ')
|> Array.map int
|> Array.rev
|> Seq.map string
|> String.concat " "
|> printfn "%s"
