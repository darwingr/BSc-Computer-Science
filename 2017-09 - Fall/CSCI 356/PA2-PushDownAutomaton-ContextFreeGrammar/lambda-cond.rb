#!/usr/bin/env ruby

l = ->(e) {
  e.class == String &&
  e > 'm' ||
  e < 'g'
}

puts "l #{l.('l')}"
puts "n #{l.('n')}"
