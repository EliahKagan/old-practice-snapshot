class Stack
  def initialize(size)
    @capacity = size
    @elems = []
  end

  def pop
    @elems.pop
  end

  def push(element)
    return nil if element.nil? || full?
    @elems.push(element)
    self
  end

  def size
    @capacity
  end

  def look
    @elems.last
  end

  private

  def full?
    @elems.length == @capacity
  end

  def empty?
    @elems.empty?
  end
end
