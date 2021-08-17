class WaiterRobot
  attr_reader :name

  def initialize(chef, tables)
    @chef = chef
    @tables = tables
    @name = "Tyler Durden"
  end

  def place_order(table_number, sandwich, drink)
    # tell the chef with Chef#new_order(waiter_robot, order_hash)
    order = {table: table_number, sandwich: sandwich, drink: drink}
    @chef.new_order(self, order)
  end

  def serve(order)
    # digest the chef's sloppy order instructions:
    # 1) find the table number you need to serve
    # 2) call Table#serve_sandwich and Table#serve_drink
    order = Hash[*order]
    table = @tables[order[:table]]
    table.serve_sandwich(order[:sandwich])
    table.serve_drink(order[:drink])
  end
end
