# Ogre class, followed by saving and loading methods for Ogre hashes
# demonstrating YAML serialization and deserialization. The 'yaml' module must
# be required by the consumer of this code. This is a completed exercise from
# http://rubymonk.com/learning/books/4-ruby-primer-ascent/chapters/45-more-classes/lessons/104-serializing
# and most text is copied verbatim, with the exception of the implementations
# of save_game and load_game.

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
  GameFile.new('savegame.yaml').write(YAML.dump(characters))
end

def load_game
  # return a deserialized hash of characters
  YAML.load(GameFile.new('savegame.yaml').read)
end
