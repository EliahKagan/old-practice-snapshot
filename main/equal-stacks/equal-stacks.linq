<Query Kind="FSharpProgram" />

let getStacks () =
    let getRecord = stdin.ReadLine >> (fun s -> s.Split ' ') >> Seq.map int
    let heights () = Seq.scanBack (+) (getRecord ()) 0 |> Seq.toList
    getRecord () |> Seq.map (ignore >> heights) |> Seq.toList

let rec equalizedHeight stacks =
    let uniform = function // true means all elements are equal to a unique value
    | x::xs -> List.forall ((=) x) xs
    | []    -> failwith "empty input not expected"
    
    let tops = stacks |> List.map List.head

    if uniform tops then
        List.head tops // return a top value (all top values are now equal)
    else
        let mintop = List.min tops
        
        let popIfNotShortest xs =
            if List.head xs = mintop then xs else List.tail xs
        
        stacks |> List.map popIfNotShortest |> equalizedHeight

getStacks () |> equalizedHeight |> printfn "%d"