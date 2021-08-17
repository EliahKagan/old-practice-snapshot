# encapsulates array just for summing, with optional mapping first
class MyArray
  attr_reader :array

  def initialize(array)
    @array = array
  end

  def sum(initial_value = 0)
    if block_given?
      @array.reduce(initial_value) { |a, e| a + yield(e) }
    else
      @array.reduce(initial_value, :+)
    end
  end
end
