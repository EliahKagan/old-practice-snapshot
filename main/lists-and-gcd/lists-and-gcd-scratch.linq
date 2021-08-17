<Query Kind="FSharpProgram" />

let gcdFactors lhs rhs =
    let rec f (xvec : int list) (yvec : int list) acc =
        match xvec, yvec with
        | xb::xp::xs, yb::yp::ys ->
            if xb = yb then     (min xp yp)::xb::acc |> f xs ys
            elif xb < yb then   acc |> f xs yvec
            else                acc |> f xvec ys
        | _ -> acc
    
    f lhs rhs [] |> List.rev

gcdFactors [7;2] [2;2;7;1] |> printfn "%A"