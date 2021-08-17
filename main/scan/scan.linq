<Query Kind="FSharpExpression" />

System.Console.ReadLine().Split()
|> Seq.map int
|> Seq.sortDescending
|> Seq.scan (+) 0
|> Seq.toArray