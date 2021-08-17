Option Explicit On
Option Strict On

Imports System.Collections.Generic
Imports System.Linq
Imports System.Runtime.CompilerServices

<Assembly: Reflection.AssemblyVersion("1.0.0.0")>

Friend Module Arith
    <Extension()>
    Friend Function Sqrt32(n As Integer) As Integer
        Return CInt(Math.Floor(Math.Sqrt(n)))
    End Function

    <Extension()>
    Friend Function Sqrt64(n As Long) As Long
        Return CLng(Math.Floor(Math.Sqrt(n)))
    End Function

    <Extension()>
    Friend Function Sqrt64To32(n As Long) As Integer
        Return CInt(Math.Floor(Math.Sqrt(n)))
    End Function

    Private Function RawSieve(n As Integer) As Boolean() ' finds primes to n
        Dim a(n) As Boolean ' false means not marked as composite

        For i = 3 To Sqrt32(n) Step 2
            If Not a(i) Then
                For j = i * i To n Step i * 2
                    a(j) = True
                Next
            End If
        Next

        Return a
    End Function

    Private Iterator Function Sieve(n As Integer) As IEnumerable(Of Long)
        Dim a = RawSieve(n)

        Yield 2L
        For k = 3 To n Step 2
            If Not a(k) Then Yield k ' int-to-long conversion happens here
        Next
    End Function

    <Extension()>
    Friend Function Primes(n As Integer) As Long() ' primes to n, as array
        Return Sieve(n).ToArray()
    End Function

    <Extension()>
    Friend Function MaxPrimeDivisorOf(primes As IEnumerable(Of Long),
                                      n As Long) As Long
        While (n And 1L) = 0L ' optimization to remove factors of 2
            n >>= 1
        End While
        If n = 1L Then Return 2L

        Dim sqrt = Sqrt64(n)
        For Each p In primes.Skip(1).TakeWhile(Function(q) q <= sqrt)
            If (n Mod p = 0L) Then
                Do
                    n \= p
                Loop While n Mod p = 0L

                If n = 1L Then Return p
            End If
        Next

        Return n ' what remains must be a single prime factor > sqrt(orig. n)
    End Function
End Module

Friend Module Solution
    Private Function ReadValues() As List(Of Long)
        Dim t = Integer.Parse(Console.ReadLine)
        ReadValues = New List(Of Long)(t)

        For i = 1 To t
            ReadValues.Add(Long.Parse(Console.ReadLine))
        Next
    End Function

    Friend Sub Main()
        Dim values = ReadValues()
        Dim primes = values.Max.Sqrt64To32.Primes

        values.ForEach(Sub(n) Console.WriteLine(primes.MaxPrimeDivisorOf(n)))
    End Sub
End Module
