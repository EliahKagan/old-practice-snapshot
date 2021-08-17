require 'yaml'

class Ogre
  attr_accessor :strength, :speed, :smell
  def initialize(strength, speed, smell)
    @strength = strength
    @speed = speed
    @smell = smell
  end
end

class Dragon
  attr_accessor :strength, :speed, :color
  def initialize(strength, speed, color)
    @strength = strength
    @speed = speed
    @color = color
  end
end

class Fairy
  attr_accessor :strength, :speed, :intelligence
  def initialize(intelligence)
    @strength = 1
    @speed = 42
    @intelligence = intelligence
  end
end

def save_game(characters)
  # serialize a character hash of :ogres, :dragons, and :fairies
  File.open('savegame.yaml', 'w') do |file|
    file.write(Psych.dump(characters))
  end
end

def load_game
  # return a deserialized hash of characters
  File.open('savegame.yaml', 'r') do |file|
    Psych.load(file.read)
  end
end
