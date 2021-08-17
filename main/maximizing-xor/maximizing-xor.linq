<Query Kind="FSharpProgram" />

let left, right =
    let get = System.Console.ReadLine >> int
    get (), get ()

{left .. right - 1}
|> Seq.collect (fun a -> {a + 1 .. right} |> Seq.map (fun b -> a ^^^ b))
|> Seq.max
|> printfn "%d"
