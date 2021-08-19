#!/usr/bin/env ruby

initial_offset = 0

# suiter line size
n = 3

# next offset: o' = o prime
# should guard: 0 <= o < 3
op = ->(o) { (n + o) % 3 }

puts "Where n = #{n}, the next offset is:"
puts "  where o = 0, #{op.(0)}"
puts "  where o = 1, #{op.(1)}"
puts "  where o = 2, #{op.(2)}"
puts

# next n: n' for n prime
# uses integer division or the floor of div
np = ->(o) { n - ((n + o) / 3) }

puts "Where n = #{n}, the next n is:"
puts "  where o = 0, #{np.(0)}"
puts "  where o = 1, #{np.(1)}"
puts "  where o = 2, #{np.(2)}"
puts

# recursed f (subproblem): fp for f' or f prime
puts "Where n = 2, position is:"
puts "  where o = 0, UNDEFINED since n' != 1"
puts "  where o = 1, 1 (1 + op)"
puts "  where o = 2, 2 (1 + op)"
puts

puts "where n = 3, position is:"
puts "  where o = 0, 2"
puts "  where o = 1, 1"
puts "  where o = 2, 3"
puts

def position(n, o = 0)
  return 1 if n == 1

  op = ->(o) { (n + o) % 3 }
  np = ->(o) { n - ((n + o) / 3) }
  sub_position = position(np.(o), op.(o))

  #sub_position + ((sub_position + o) / 3)
  #n - (np.(o) - sub_position)
end

puts "where n = #{n}, position is:"
puts "  where o = 0, #{position(n, 0)}"
puts "  where o = 1, #{position(n, 1)}"
puts "  where o = 2, #{position(n, 2)}"
puts

puts " Suiters | Selected "
puts "   (n)   | Position "
puts "---------|----------"
(2..20).each do |n|
  print "%11s" % "#{n}  | "
  puts  "%3s" % position(n)
end

puts "-------------------------------"
puts

