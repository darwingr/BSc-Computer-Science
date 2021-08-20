#! /usr/bin/env ruby
#
# This program accepts and outputs characters until the substring "abba"
# is found. The equivalent regular expression is
#   (a ∪ b)* abba (a ∪ b)*
#
# It has a Boolean function for each state, which
# a) returns true if it is a final state, or
# b) processes and outputs a single letter from the input and
#   i)  returns a call to the state reached by following that letter from the
#       current state, or
#   ii) returns a call to state q_0 if any other character is encountered.

require 'io/console'

def get_char
  #STDIN.getch
  STDIN.getc
end

# Returns a boolean value via the final state q4
def q0
  letter = get_char
  print letter
  return q1 if letter == 'a'
  return q0 if letter == 'b'
  return q0
end

def q1
  letter = get_char
  print letter
  return q1 if letter == 'a'
  return q2 if letter == 'b'
  return q0
end

def q2
  letter = get_char
  print letter
  return q1 if letter == 'a'
  return q3 if letter == 'b'
  return q0
end

def q3
  letter = get_char
  print letter
  return q4 if letter == 'a'
  return q0 if letter == 'b'
  return q0
end

# Returns a boolean value, true if final state is reached.
# We don't actually execute the loop on q4 so it's disabled here.
def q4
  #letter = get_char
  #print letter
  #return q4 if letter == 'a' || letter == 'b'
  return true
end

puts "Pass in any word."
puts "Program will end if word contains 'abba'.\n"
q0
