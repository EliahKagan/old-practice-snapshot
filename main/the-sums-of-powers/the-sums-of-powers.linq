<Query Kind="FSharpProgram" />

let rec ( ** ) b = function
| 1 -> b
| e ->
    let r = b**(e / 2)
    let s = r * r
    
    match e % 2 with
    | 0 -> s
    | _ -> s * b

let powers exponent stop =
    let rec generate start acc =
        if start < stop then
            start**exponent::acc |> generate (start + 1)
        else
            acc
    
    generate 1 [] |> List.rev

let countDistinctPowerSums x n =
    //let ps = powers n x
    
    let rec count 

let x, n =
    let getval = System.Console.ReadLine >> int
    getval (), getval()



//let countDistinctPowerSums