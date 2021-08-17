<Query Kind="FSharpProgram" />

let hour = function
    | 1 -> "one"
    | 2 -> "two"
    | 3 -> "three"
    | 4 -> "four"
    | 5 -> "five"
    | 6 -> "six"
    | 7 -> "seven"
    | 8 -> "eight"
    | 9 -> "nine"
    | 10 -> "ten"
    | 11 -> "eleven"
    | 12 -> "twelve"
    | _ -> failwith "hour text lookup failed"

let minute = function
    | 1 -> "one minute"
    | 2 -> "two minutes"
    | 3 -> "three minutes"
    | 4 -> "four minutes"
    | 5 -> "five minutes"
    | 6 -> "six minutes"
    | 7 -> "seven minutes"
    | 8 -> "eight minutes"
    | 9 -> "nine minutes"
    | 10 -> "ten minutes"
    | 11 -> "eleven minutes"
    | 12 -> "twelve minutes"
    | 13 -> "thirteen minutes"
    | 14 -> "fourteen minutes"
    | 15 -> "quarter"
    | 16 -> "sixteen minutes"
    | 17 -> "seventeen minutes"
    | 18 -> "eighteen minutes"
    | 19 -> "nineteen minutes"
    | 20 -> "twenty minutes"
    | 21 -> "twenty one minutes"
    | 22 -> "twenty two minutes"
    | 23 -> "twenty three minutes"
    | 24 -> "twenty four minutes"
    | 25 -> "twenty five minutes"
    | 26 -> "twenty six minutes"
    | 27 -> "twenty seven minutes"
    | 28 -> "twenty eight minutes"
    | 29 -> "twenty nine minutes"
    | 30 -> "half"
    | _ -> failwith "minute text lookup failed"

let time h = function
    | 0              ->  hour h |> sprintf "%s o' clock"
    | m when m <= 30 ->  hour h |> sprintf "%s past %s" (minute m)
    | m              ->  h + 1 |> hour |> sprintf "%s to %s" (60 - m |> minute)

let get = System.Console.ReadLine >> int
time (get ()) (get ()) |> printfn "%s"
