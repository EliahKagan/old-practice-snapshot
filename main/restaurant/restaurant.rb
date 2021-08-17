# maintains a menu and computes costs of single and multiple orders
class Restaurant
  def initialize(menu)
    @menu = menu
  end

  # computes the cost of the single order passed as an argument
  def single_cost(order)
    order.keys.reduce(0) { |a, e| a + order[e] * @menu[e] }
  end

  # computes the cost of all orders passed as arguments
  def cost(*orders)
    orders.reduce(0) { |a, e| a + single_cost(e) }
  end
end
