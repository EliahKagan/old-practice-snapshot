<Query Kind="FSharpProgram" />

module BalancedStrings =
    open System.Text.RegularExpressions

    [<Literal>]
    let private rgBalanced = "(?=[YB]*(?:R[YB]*G[YB]*|G[YB]*R[YB]*)*$)"
    
    [<Literal>]
    let private ybBalanced = "[RG]*(?:Y[RG]*B[RG]*|B[RG]*Y[RG]*)*"
    
    [<Literal>]
    let private pattern = "^" + rgBalanced + ybBalanced + "$"
    
    [<Literal>]
    let private options =
        RegexOptions.Compiled ||| RegexOptions.CultureInvariant
    
    let private regex = Regex (pattern, options)
    
    let fullOfColors (s:string) = (s.Trim () |> regex.Match).Success

{1..(System.Console.ReadLine () |> int)}
|> Seq.iter (ignore
             >> System.Console.ReadLine
             >> BalancedStrings.fullOfColors
             >> string
             >> printfn "%s")