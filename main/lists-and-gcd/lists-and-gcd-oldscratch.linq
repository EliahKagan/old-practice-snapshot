<Query Kind="FSharpProgram" />

open System

let gcdFactors lhs rhs =
    let rec f (xvec : int list) (yvec : int list) acc =
        match xvec, yvec with
        | xb::xp::xs, yb::yp::ys ->
            match xb - yb |> Math.Sign with
            | 0  -> (min xp yp)::xb::acc |> f xs ys
            | -1 -> acc |> f xs yvec
            | 1  -> acc |> f xvec ys
            | _  -> failwith "invalid signum (internal error)"
        | _ -> acc
    
    f lhs rhs [] |> List.rev

gcdFactors [7;2] [2;2;7;1] |> printfn "%A"