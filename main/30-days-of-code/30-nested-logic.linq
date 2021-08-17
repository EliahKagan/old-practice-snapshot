<Query Kind="FSharpProgram" />

let day   (date:int[]) = date.[0]
let month (date:int[]) = date.[1]
let year  (date:int[]) = date.[2]

let get =
    let split (s:string) = s.Split ' '
    System.Console.ReadLine >> split >> Array.map int

let fine returned due =
    if   year  returned  <  year due   then 0
    elif year  returned  >  year due   then 10000
    elif month returned  <  month due  then 0
    elif month returned  >  month due  then (month returned - month due) * 500
    elif day   returned  <= day due    then 0
    else                                    (day returned - day due) * 15

fine (get ()) (get ()) |> printfn "%d"
