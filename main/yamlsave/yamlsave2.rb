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
  #File.write('savegame.yaml', Psych.dump(characters))
  GameFile.new('savegame.yaml').write(Psych.dump(characters))
end

def load_game
  # return a deserialized hash of characters
  #Psych.load(File.read('savegame.yaml'))
  Psych.load(GameFile.new('savegame.yaml').read)
end
