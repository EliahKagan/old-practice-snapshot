module Queue =
    let inline make<'a> () = ([], []) : 'a list * 'a list

    let enqueue x (xs, ys) = x::xs, ys
    
    let private recharge = function
    | ([], [])  -> failwith "operation invalid on empty queue"
    | (xs, [])  -> [], List.rev xs
    | q         -> q
    
    let peek action q = // carries out the action on the front element
        let r = recharge q
        r |> snd |> List.head |> action
        r
    
    let dequeue q =
        let r = recharge q
        fst r, snd r |> List.tail

let queries =
    let interpret = function
    | [|1; x|]  -> Queue.enqueue x
    | [|2|]     -> Queue.dequeue
    | [|3|]     -> Queue.peek stdout.WriteLine
    | _         -> failwith "unrecognized query type"

    let getln = stdin.ReadLine
    let inline split (s : string) = s.Split ' '
    let nq = getln () |> int
    {1..nq} |> Seq.map (ignore >> getln >> split >> Array.map int >> interpret)

queries |> Seq.fold (|>) (Queue.make<int> ()) |> ignore
