<Query Kind="FSharpProgram" />

let countConfigurations n =
    let safeFrom i j qi qj =
        // A knight in chess is a Knight(1, 2).
        let a = 1
        let b = 2
        
        let di = i - qi
        assert (di > 0)
        let dj = j - qj |> abs
        
        // A "super-queen" or "empress" can attack...
        dj <> 0                                             // like a rook...
            && dj <> di                                     // or a bishop...
            && (di <> a || dj <> b) && (di <> b || dj <> a) // or a knight.
    
    let rec safe i j = function
        | (qi, qj)::qs ->
            safeFrom i j qi qj && safe i j qs
        | [] ->
            true
    
    let rec count i qs =
        if i = n then
            //qs |> printfn "%A"
            1
        else
            {0..n - 1}
            |> Seq.filter (fun j -> qs |> safe i j)
            |> Seq.sumBy (fun j -> (i, j)::qs |> count (i + 1))
    
    [] |> count 0

let test n =
    printfn "%d:" n
    countConfigurations n |> printfn "%d"
    printfn ""

{8..16} |> Seq.iter test
