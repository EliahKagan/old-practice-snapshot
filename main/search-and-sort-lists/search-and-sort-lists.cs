var names = new List<string> {"Eliah", "Ana", "Felipe"};

void Show()
{
    names.ForEach(name => Console.WriteLine($"Hello, {name.ToUpper()}!"));
    
    Console.WriteLine();
}

Show();

names.Add("Maria");
names.Add("Bill");
names.Remove("Ana");

Show();

Console.WriteLine($"My name is {names[0]}.");
Console.WriteLine($"I've added {names[2]} and {names[3]} to the list.");
Console.WriteLine($"The list has {names.Count} people in it.");
Console.WriteLine();

var index = names.IndexOf("Felipe");
if (index != -1)
    Console.WriteLine($"The name {names[index]} is at index {index}.");

var notFound = names.IndexOf("Ana");
Console.WriteLine($"When an item is not found, IndexOf returns {notFound}.");

Console.WriteLine();

names.Sort();
Show();
