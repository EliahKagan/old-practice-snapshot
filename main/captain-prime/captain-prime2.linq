<Query Kind="FSharpProgram" />

module Prime =
    let private isqrt n = n |> float |> sqrt |> int // precise on 32-bit ints
    
    let primes n = // Returns the set of primes up to n. (Functional, eager.)
        let imin, imax = 3, isqrt n
    
        let rec sieve i cur =
            if i > imax then
                cur
            else
                let next =
                    if cur |> Set.contains i then
                        cur - set {(i * i)..(i * 2)..n}
                    else
                        cur
    
                sieve (i + 2) next
    
        {imin..2..n} |> Seq.append [2] |> set |> sieve imin
    
    [<Literal>]
    let private nmax = 1000000
    
    let private smallPrimes = nmax |> isqrt |> primes
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