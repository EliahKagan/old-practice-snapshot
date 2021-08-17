<Query Kind="Statements">
  <Reference>&lt;RuntimeDirectory&gt;\System.Numerics.dll</Reference>
  <Namespace>System.Linq</Namespace>
  <Namespace>System.Numerics</Namespace>
</Query>

List<long> CountPairs(IList<long> sizes)
{
    var sum = sizes.Sum();
    return sizes.Select(size => size * (sum -= size)).ToList();
}

IEnumerable<long> CountTriplets(IList<long> sizes)
{
    var pairCounts = CountPairs(sizes);
    var sum = pairCounts.Sum();
    
    return sizes.Zip(pairCounts,
                     (size, pairCount) => size * (sum -= pairCount));
}

long CountAllTriplets(IList<long> sizes) => CountTriplets(sizes).Sum();

CountAllTriplets(new long[] { 3, 5, 7, 2 }).Dump();