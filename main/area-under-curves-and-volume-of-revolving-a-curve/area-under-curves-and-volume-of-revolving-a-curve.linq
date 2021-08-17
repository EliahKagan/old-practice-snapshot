<Query Kind="FSharpProgram" />

open System

[<Literal>]
let delta = 0.001

let circleArea r = r * r * Math.PI

let terms =
    let monomial coefficient exponent = fun x -> coefficient * x**exponent
    
    let coefficients, exponents =
        let get = Console.ReadLine >> (fun s -> s.Split ' ') >> Seq.map float
        get (), get ()
    
    Seq.map2 monomial coefficients exponents |> Seq.toArray

let fn x = terms |> Array.sumBy (fun f -> f x)

let preimage =
    let lowerBound, upperBound =
        let tokens = Console.ReadLine().Split ' ' |> Array.map float
        tokens.[0], tokens.[1]
    
    {lowerBound..delta..(upperBound(* - delta*))}

let image = preimage |> Seq.map fn |> Seq.toArray

Array.sum image * delta |> printfn "%f"
Array.sumBy circleArea image * delta |> printfn "%f"