<Query Kind="FSharpProgram" />

module Prime =
    let private isqrt n = n |> float |> sqrt |> int // precise on 32-bit ints
    
    let private sieve n = // Returns the set of primes up to n.
        let (a : bool array) = n + 1 |> Array.zeroCreate // true => composite
        
        for i in {3..2..(isqrt n)} do
            if not a.[i] then
                for j in {(i * i)..(i * 2)..n} do a.[j] <- true
        
        {3..2..n} |> Seq.filter (fun i -> not a.[i]) |> Seq.append [2] |> set
    
    [<Literal>]
    let private nmax = 1000000
    
    let private smallPrimes = nmax |> isqrt |> sieve
    let private maxSmallPrime = Set.maxElement smallPrimes
    
    let prime n = // For 0 <= n <= nmax, returns true iff n is prime.
        smallPrimes |>
            if n > maxSmallPrime then
                let pmax = isqrt n
                Seq.takeWhile (fun p -> p <= pmax)
                >> Seq.forall (fun p -> n % p <> 0)
            else
                Set.contains n

module Trunc =
    type Truncatability = Neither | Left | Right | Both

    let private rightTruncs str =
        {0..(String.length str - 2)} |> Seq.map (fun i -> str.[0..i])
    
    let private leftTruncs str =
        let imax = String.length str - 1
        {imax..(-1)..1} |> Seq.map (fun i -> str.[i..imax])
    
    let private truncatability predicate str =
        if predicate str then
            let allIn generator = str |> generator |> Seq.forall predicate
            
            match allIn rightTruncs, allIn leftTruncs with
            | true, true    -> Both
            | false, true   -> Left
            | true, false   -> Right
            | false, false  -> Neither
        else
            Neither
    
    let numeralTruncatability integralPredicate n =
        let str = string n
        
        if Seq.contains '0' str then
            Neither
        else
            str |> truncatability (int >> integralPredicate)

open Trunc

let fate id =
    match id |> numeralTruncatability Prime.prime with
    | Both      -> "CENTRAL"
    | Left      -> "LEFT"
    | Right     -> "RIGHT"
    | Neither   -> "DEAD"

let get = System.Console.ReadLine >> int

{1..(get ())} |> Seq.iter (ignore >> get >> fate >> printfn "%s")