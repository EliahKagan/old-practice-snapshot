# A simple stack implemented as a fixed-size array.
class Stack
  def initialize(size)
    @store = Array.new(size)
    @index = 0
  end

  def pop
    @store[@index -= 1] unless empty?
  end

  def push(element)
    return nil if full? || element.nil?
    @store[@index] = element
    @index += 1
    self
  end

  def size
    @store.size
  end

  def look
    @store[@index - 1] unless empty?
  end

  private

  def full?
    @index == size
  end

  def empty?
    @index == 0
  end
end
