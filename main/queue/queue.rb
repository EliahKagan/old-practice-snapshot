class Queue
  def initialize(size)
    @capacity = size
    @elems = []
  end

  def dequeue
    @elems.shift
  end

  def enqueue(element)
    return nil if element.nil? || full?
    @elems.push(element)
    self
  end

  def size
    @capacity
  end

  private

  def full?
    @elems.length == @capacity
  end

  def empty?
    @elems.empty?
  end
end
