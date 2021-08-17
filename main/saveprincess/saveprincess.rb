#!/usr/bin/env ruby
$VERBOSE = true

size = gets.to_i
mi = mj = pi = pj = nil

(0...size).each do |i|
  row = gets.strip
  raise 'wrong row length' if row.length != size

  row.each_char.each_with_index do |e, j|
    case e
    when '-'
      next
    when 'm'
      raise 'multiple bot starting positions observed' if mi
      mi = i
      mj = j
    when 'p'
      raise 'multiple princess starting positions observed' if pi
      pi = i
      pj = j
    else
      raise 'unrecognized character observed in cell'
    end
  end
end

raise 'no bot position observed' unless mi
raise 'no princess position observed' unless pi

(mi...pi).each { puts 'DOWN' }
(pi...mi).each { puts 'UP' }
(mj...pj).each { puts 'RIGHT' }
(pj...mj).each { puts 'LEFT' }
