unless Enumerable.method_defined?(:sum)
  # Define a quick and dirty sum (assumes integers and no block).
  module Enumerable
    def sum
      reduce(0, :+)
    end
  end
end

def count_pairs(sizes)
  sum = sizes.sum
  sizes.map { |size| size * (sum -= size) }
end

def count_triplets(sizes)
  pair_counts = count_pairs(sizes)
  sum = pair_counts.sum

  sizes.lazy.zip(pair_counts).map do |size, pair_count|
    size * (sum -= pair_count)
  end
end
