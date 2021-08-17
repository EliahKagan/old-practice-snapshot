<Query Kind="FSharpProgram" />

open Checked

module StringReversal =
    // Reverses a string, Way A: make array, make reversed array, make string.
    let reverseA (s : string) =
        s.ToCharArray () |> Array.rev |> System.String
    
    // Reverses a string, Way B: make array, reverse it in place, make string.
    let reverseB (s : string) =
        let revInPlace (a : 'a array) =
            let rec r i j =
                if i < j then
                    let tmp = a.[i]
                    a.[i] <- a.[j]
                    a.[j] <- tmp
                    r (i + 1) (j - 1)
                else
                    a
        
            Array.length a - 1 |> r 0
        
        s.ToCharArray () |> revInPlace |> System.String
    
    let test () = // string reversal unit test
        let s = "abcdefghijklmnopqrstuvwxyz"
        let t = "Madam, I'm Adam"
        let u = ""
    
        [reverseA; reverseB]
        |> List.iter (fun f -> printfn "%A" [f s; f t; f u])

module Fibonacci =
    // Computes the fibonacci sequence with the tail recursive O(n) algorithm.
    let inline fibonacci (n : 'a) =
        let zero : 'a = LanguagePrimitives.GenericZero
        let one : 'a = LanguagePrimitives.GenericOne
    
        let rec fib a b n' =
            if n' = zero then a else fib b (a + b) (n' - one)
        
        if n < zero then
            failwith "Fibonacci sequences have no negatively indexed positions"
        else
            fib zero one n
    
    let test () =
        [0..10] |> List.map fibonacci |> printfn "%A"
        200I |> fibonacci |> printfn "%A"
        
        try
            fibonacci -1L |> printfn "%d"
        with
        | e -> eprintfn "error: %s" e.Message

module CayleyTable =
    // Prints a Cayley table for the specified operator, left operand domain,
    // right operand domain, and minimum column width, Way A: row by row.
    let rec printA operator leftDomain rightDomain width =
        match leftDomain with
        | []    -> () // no more rows
        | x::xs ->
            rightDomain
            |> List.map (operator x >> sprintf "%*d" width)
            |> String.concat " "
            |> stdout.WriteLine // outside LINQPad, should use:  printfn "%s"
            
            printA operator xs rightDomain width
    
    // Prints a Cayley table for the specified operator, left operand domain,
    // right operand domain, and minimum column width, Way B: cell by cell.
    let printB operator leftDomain rightDomain width =
        let format = sprintf "%*d" width
    
        for x in leftDomain do
            match rightDomain with
            | y::ys ->
                operator x y |> format |> stdout.Write
                
                for y' in ys do
                    stdout.Write ' '
                    operator x y' |> format |> stdout.Write
                
                stdout.WriteLine ()
            | []    -> ()
    
    // Prints a Cayley table for the specified operator, left operand domain,
    // and right operand domain, Way C: inferring the appropriate column width.
    let printC operator leftDomain rightDomain =
        let table =
            let row x = rightDomain |> List.map (operator x >> sprintf "%A")
            leftDomain |> List.map row
        
        let cell =
            let maxWidthInRow = Seq.map String.length >> Seq.max
            let width = table |> Seq.map maxWidthInRow |> Seq.max
            sprintf "%*s" width
        
        table
        |> List.map (List.map cell >> String.concat " ")
        |> String.concat System.Environment.NewLine
        |> printfn "%s"
    
    // Prints a Cayley table for the specified operator, left operand domain,
    // and right operand domain, Way D: inferring minimum uniform width for
    // each column separately.
    let printD operator leftDomain rightDomain =
        let transpose cols =
            let rec tr acc cols' =
                if cols' |> List.head |> List.isEmpty then
                    acc
                else
                    List.map List.tail cols'
                    |> tr ((List.map List.head cols')::acc)
            
            cols |> tr [] |> List.rev
    
        let column y =
            let applyLeft x = operator x y
            let col = leftDomain |> List.map (applyLeft >> sprintf "%A")
            let pad = col |> Seq.map String.length |> Seq.max |> sprintf "%*s"
            col |> List.map pad
        
        let rows = rightDomain |> List.map column |> transpose
        
        List.map (String.concat " ") rows
        |> String.concat System.Environment.NewLine
        |> printfn "%s"
    
    let test () =
        // print 12x12 multiplication tables, with no row/col labels
        let dom = [1..12]
        [printA; printB] |> List.iter (fun f -> f (*) dom dom 3; printfn "")
        [printC; printD] |> List.iter (fun f -> f (*) dom dom)
        
        // print [25..35]**2 multiplication tables to show auto width sensing
        let dom2 = [25..35]
        [printC; printD] |> List.iter (fun f -> f (*) dom2 dom2)
        
        // print some small powers, to contrast printC with printD
        [printC; printD] |> List.iter (fun f -> f ( ** ) [1I..8I] [1..8])

module FileData =
    open System.IO
    open System.Security
    open System.Text.RegularExpressions
    
    type Try<'a> =
    | Good  of 'a       // value
    | Bad   of string   // message
    
    let tryIO operation arg =
        try
            operation arg |> Good
        with
        | :? ArgumentNullException              -> reraise ()
        | :? ArgumentException
        | :? IOException
        | :? SecurityException
        | :? UnauthorizedAccessException as e   -> Bad e.Message
    
    // Computes the sum of all integers in a file, where each line of the file
    // contains a single integer (and optional leading/trailing whitespace),
    // Way A: read file's lines with an explicit tail-recursive helper function.
    let sumFromFileA (path : string) =
        use reader = new StreamReader(path)
        
        let rec sum acc =
            match reader.ReadLine () with
            | null  -> acc
            | line  -> acc + int line |> sum
        
        sum 0
    
    // Computes the sum of all integers in a file, where each line of the file
    // contains a single integer (and optional leading/trailing whitespace),
    // Way B: read file's lines with File.ReadLines.
    let sumFromFileB path =
        path |> File.ReadLines |> Seq.map int |> Seq.sum
    
    // These functions compute the sum of all integers in a file, like
    // sumFromFileA and sumFromFileB (by calling those functons, respectively),
    // but returns error messages for documented errors.
    let trySumFromFileA = tryIO sumFromFileA
    let trySumFromFileB = tryIO sumFromFileB
    
    let test () =
        let topLine (s : string) = Regex.Split(s, @"\r?\n").[0]
    
        let seqToTempFile (sequence : 'a seq) =
            let path = Path.GetTempFileName ()
            use writer = new StreamWriter(path, true)
            sequence |> Seq.iter writer.WriteLine
            path
        
        let goodPath = seqToTempFile {1..100}
        
        for path in [goodPath; "nonexistent.txt"; @"C:\"; ""] do
            for operation in [trySumFromFileA; trySumFromFileB] do
                match operation path with
                | Good n    -> printfn "%d" n
                | Bad msg   -> topLine msg |> eprintfn "error: %s"
        
        File.Delete goodPath

module TrivialArithmetic =
    // Prints the odd numbers between 1 and 99, inclusive, one per line.
    let printSmallOddNumbers () = {1..2..99} |> Seq.iter (printfn "%d")

module Extremization =
    // Finds the maximum value in an enumerable collection. Works with arrays,
    // since they are enumerable. Using Array.max would also be perfectly good,
    // though less general. This is Way A: just use Seq.max.
    let maxValueA = Seq.max
    
    // Finds the maximum value, Way B: reimplementing Seq.max's functionality.
    let maxValueB sequence =
        let mutable acc = System.Int32.MinValue
        
        for value in sequence do
            if acc < value then acc <- value
        
        acc
    
    // Finds the maximum value, Way C: an array-specific manual fold.
    let maxValueC (a : int array) =
        let rec maxval acc = function
        | 0 -> acc
        | n ->
            let i = n - 1
            maxval (if acc < a.[i] then a.[i] else acc) i
        
        Array.length a |> maxval System.Int32.MinValue
    
    let test () =
        let a = [|10; 30; 20; -1; 90; 98; 4; 15|]
        
        printfn "max value: %d, %d, %d"
                (maxValueA a) (maxValueB a) (maxValueC a)

module Format =
    let rgb = sprintf "%02X%02X%02X"
    
    let test () = rgb 255 0 128 |> printfn "%s"

StringReversal.test ()
Fibonacci.test ()
CayleyTable.test ()
FileData.test ()
TrivialArithmetic.printSmallOddNumbers ()
Extremization.test ()
Format.test()