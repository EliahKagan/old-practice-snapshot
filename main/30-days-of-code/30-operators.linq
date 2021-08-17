<Query Kind="FSharpProgram" />

let meal, tip, tax =
    let get = System.Console.ReadLine >> float in get (), get (), get ()

meal + (meal * tip / 100.) + (meal * tax / 100.)
    |> printfn "The total meal cost is %.0f dollars."
