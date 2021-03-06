<Query Kind="FSharpProgram" />

let gcdFactors lhs rhs =
    let rec f xvec yvec acc =
        match xvec, yvec with
        | xb::xp::xs, yb::yp::ys ->
            if xb = yb then     (min xp yp)::xb::acc |> f xs ys
            elif xb < yb then   acc |> f xs yvec
            else                acc |> f xvec ys
        | _ -> acc
    
    f lhs rhs [] |> List.rev

let getln = System.Console.ReadLine
let getRecord = getln >> (fun s -> s.Split ' ') >> Seq.map int >> Seq.toList

{1..(getln () |> int)}
|> Seq.map (ignore >> getRecord)
|> Seq.reduce gcdFactors
|> Seq.map string
|> String.concat " "
|> printfn "%s"