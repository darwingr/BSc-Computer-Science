# encoding: UTF-8
#
# file: delimiter_matcher.rb

require './tape'

# This implementation of a deterministic PDA specifically matches delimiters.
# Feed it a tape before executing transitions.
#
# Deterministic Pushdown Automata
# Formally defined as a septuple:
#   M = (𝑸, 𝚺, 𝚪, 𝜹, q₀, 𝐙₀, 𝐅)
# This implementation is constructed as:
#   m = DelimiterMatcher.new
#
class DelimiterMatcher

  def initialize
    @stack_alphabet = ['(', '<', '[', '{']
    @start_state = :q0

    # to be matched by index
    @match_alphabet = [')', '>', ']', '}']

    # Actual PDA memory
    @stack = []
    @state = ''
    @tape
  end

  # The same pda object can be used on different input tapes.
  # It will always reset the state and stack.
  def feed_tape(input)
    @tape = Tape.new input
    @stack = []
    @state = @start_state
  end

  def execute_transitions
    send @start_state
  end

  private

  # States transitions:
  #   1. end of tape and stack  (accepting)
  #   2. left delim             y, ⊥/y
  #   3. ascii (not right)      x, ⊥/λ
  #   4. not ascii              (crashing)
  #  (5.) right delim?          (crashing)
  #
  def q0
    @tape.shift_head

    if @tape.end? && @stack.empty?
      puts 'ACCEPT'
      return true
    end

    # y, ⊥/y
    if @stack_alphabet.include? @tape.head
      # stack was empty
      @stack.push @tape.head
      return q1
    end

    # x, ⊥/λ
    if char_is_ascii?
      return q0
    end

    crash
  end

  # State transitions:
  #   1. end of tape & stack  λ, ⊥/λ
  #   2. left delim           y, z/yz     where z is some delim, not empty
  #   3. right delim          y', y/λ
  #   4. ascii                x, y/y
  #   5. not ascii            (crashing)
  #   6. right with wrong left(crashing)
  #  (7.) right with no left  (crashing)
  #   8. end of tape          (crashing)
  def q1
    @state = :q1
    @tape.shift_head

    # y, z/yz       where z is some delim, not empty
    if @stack_alphabet.include? @tape.head
      @stack.push @tape.head
      return q1
    end

    # y', y/λ
    if tape_head_matches_stack?
      @stack.pop
      return q1
    end

    # λ, ⊥/λ
    if @tape.end? && @stack.empty?
      return q0
    end

    # x, y/y
    if char_is_ascii?
      return q1
    end

    crash
  end

  # halt: accept, crash or reject
  def crash
    puts "REJECT"
    puts "    Mistake while tape at position #{@tape.position}."
    puts "    Tape head currently reads #{@tape.head.inspect}."
    puts "    Expected to see match for #{top_of_stack.inspect}."
    puts "    Halted in state #{@state.to_s}."
    return false
  end

  # Char on the tape head
  def char_is_ascii?
    return false if @tape.end?
    # Right matching symbols, y', is part of the input alphabet however we
    # cannot consider it valid criteria for transition.
    return false if @match_alphabet.include? @tape.head
    @tape.head.ascii_only?
  end

  def tape_head_matches_stack?
    index = @stack_alphabet.find_index top_of_stack
    return false if index.nil?
    match_from_stack = @match_alphabet[index]
    return true if @tape.head == match_from_stack
    return false
  end

  def top_of_stack
    @stack.last
  end
end
