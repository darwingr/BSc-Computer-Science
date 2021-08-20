#!/usr/bin/env ruby

require 'io/console'
require './tmdisplay'

ARGV.include?('-v') ? verbose = true : verbose = false

# Arbitrary deterministic Turing Machine
#
# The visual display of configuration sequences as the machine performs its
# computation is streamed to StdErr.
# The HALT signal, acceptance message and the final contents of the tape is
# streamed to StdOut.

$stderr.puts "Loading instruction table"
instructions_table = []
loop do
  line = $stdin.gets
  # chomp: removes all trailing newlines, won't work if nil
  break if line.nil? || line.chomp == "-1"
  $stderr.puts "#{$stdin.lineno} : #{line.chomp.inspect}" if verbose
  instructions_table.push line.chomp
end
$stderr.puts "found sentinel on line #{$stdin.lineno}"

input_string = $stdin.gets.chomp
$stderr.puts "\nInput string: #{input_string.inspect}, "\
             "size: #{input_string.length}"
input_string.prepend ' ' if input_string[0] != ' '
tape = input_string

final_states = []
state = 0
position = 0

print_tape_head_diagram tape, state, position

# To permit acceptance by final state, enter on separate lines followed by -1
loop do
  line = $stdin.gets#.chomp # won't work if nil
  break if line.nil? || line.chomp == "-1"
  final_states.push line.hex
end
$stderr.puts "\nAccepting Final States: #{final_states}"

$stderr.puts "\nBEGIN EXECUTION"
loop do
  # Filter to find next instruction
  state_instructions = instructions_table.select {|ins| ins[0].hex == state }
  $stderr.puts "\n1. Instructions for current state: "\
               "#{state_instructions.inspect}" if verbose
  possible_instructions = state_instructions.select do |ins|
    ins[1] == tape[position]
  end
  $stderr.puts "2. Possible instructions: "\
               "#{possible_instructions.inspect}" if verbose
  if possible_instructions.empty?
    # DEFINITION: a TM halts when it reaches a state/symbol pair for which no
    #             transition is defined. (from class notes)
    $stdout.puts "HALT"
    break
  end
  next_instruction = possible_instructions.first
  $stderr.puts "3. Excecuting next instruction: "\
               "#{next_instruction.inspect}" if verbose

  # execute next instruction
  state = next_instruction[2].hex
  tape[position] = next_instruction[3]
  position += 1 if next_instruction[4] == 'R'
  position -= 1 if next_instruction[4] == 'L'
  # same position if 'S'
  $stderr.puts "position: #{position}" if verbose

  # Add blanks if needed, also needed for tape with only blank
  tape.concat ' ' if tape[position].nil?

  print_tape_head_diagram tape, state, position
end

if final_states.include? state
  $stdout.puts "ACCEPT"
elsif !(final_states.empty?)
  $stdout.puts "REJECT"
end
$stdout.puts tape

exit 0
