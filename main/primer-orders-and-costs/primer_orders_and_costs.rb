class Restaurant
  def initialize(menu)
    @menu = menu
  end

  def order_cost(order)
    order.map { |item, count| @menu[item] * count }.reduce(0, :+)
  end

  def cost(*orders)
    orders.reduce(0) { |a, e| a + order_cost(e) }
  end
end
