<Query Kind="Program" />

class Multiplier {
    public Multiplier(double value) => Value = value;

    public double Scale(double multiplicand)
        => multiplicand * Value;
    
    public double ScaleTwice(double multiplicand)
        => multiplicand * Value * Value;
    
    public double Value { get; }
}

/// <summary>Why would anyone multiply, except by 10?</summary>
class NamedTenMultiplier {
    public NamedTenMultiplier(string name) => Name = name;

    /// <summary>Multiplies by 10.</summary>
    /// <remarks>Could be a static method.</remarks>
    public double ScaleByTen(double multiplicand)
        => multiplicand * 10;
    
    public string Name { get; }
}

delegate double Scaling(double multiplicand);

static class Program {
    private static void Main()
    {
        Multiplier by_three = new Multiplier(3.0);
        Scaling f = by_three.Scale;
        Scaling g = by_three.ScaleTwice;
        Scaling h = new NamedTenMultiplier("Jean-Luc").ScaleByTen;
        Scaling i = x => x * 7;
        
        Scaling[] scalings = { f, g, h, i };
        
        Array.ForEach(scalings, sca => Console.WriteLine(sca(1.5)));
        Console.WriteLine();
        
        foreach (var sca in scalings) {
            switch (sca.Target) {
            case Multiplier mul:
                Console.WriteLine($"Got a {mul.Value} multiplier.");
                break;
            
            case NamedTenMultiplier ntm:
                Console.WriteLine($"{ntm.Name} only multiplies by 10.");
                break;
            
            default:
                Console.WriteLine("Delegate target is some other type or null.");
                break;
            }
        }
    }
}
