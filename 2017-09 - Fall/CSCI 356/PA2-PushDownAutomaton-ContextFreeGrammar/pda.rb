# encoding: UTF-8
#
# file: pda.rb

require './tape'

# Deterministic Pushdown Automata
# Formally defined as a septuple:
#   M = (𝑸, 𝚺, 𝚪, 𝜹, q₀, 𝐙₀, 𝐅)
# Constructed as:
#   m = PDA.new(𝑸, 𝚺, 𝚪, 𝜹, q₀, 𝐙₀, 𝐅)
#
# This implementation is an improvement over the previous for PDA
# implementation for 2 important reasons:
#
#   1. A generic deterministic PDA object where all the transition relation is
#   defined at construction. Thus it can be reused for constructing many
#   different kinds of deterministic PDAs. This also avoids hard coded
#   "state-functions" (e.g. q0, q1), the term being an oxy-moron, in our PDA
#   which is more meaningful.
#
#   2. The construction of the PDA object is expressed in the same way it
#   in the written theory form; as a heptuple. Again, this leads to greater
#   semantic clarity and consistency. An effort has also been made to stay
#   consistent with the types used, for exampl treating the alphabets as sets
#   and q₀ as a single value. A language like ML or Haskell could really
#   improve and take more advantage of it by defining these more explicitly.
#
# Notes on attributes:
#
# Alphabets can be defined either explicitly by the set using an array or by
# construction, like with set builder notation, using a lambda of conditionals.
#
# The stack alphabet can be defined as an array or a hash, which allows us to
# sneak in our matching characters (y') for a matching PDA. In that case it's
# also important to exclude both the stack alphabet and the matching characters
# from the input alphabet. In its current implementation, this necessary in
# order to be deterministic.
#
# The transition relation is passed in as a set of tuples which reflects the
# following function:
#   𝜹:𝑸 x 𝚺 x 𝚪* -> P(𝑸 x 𝚪*)
#
#   For the matching PDA:
#   𝜹(q_i, (x or y or y'), (z or ⊥)) = (q_j, (yz or λ))
#
#
#
class PDA

  def initialize(states, input_alphabet, stack_alphabet, transition_relation,
                 start_state, start_stack_symbol, accepting_states)
    @states = states.map {|e| e.to_sym } # can be used to validate
    # Define set explicitly or by construction
    @input_alphabet = input_alphabet
    @stack_alphabet = stack_alphabet
    @transition_relation = transition_relation    # these should be validated
    @start_state = start_state.to_sym
    @start_stack_symbol = start_stack_symbol # should be non-ascii
    @accepting_states = accepting_states.map {|e| e.to_sym }

    # Actual PDA memory
    @state = '' # do first transition when inserting tape?
    @stack = []
    @tape
  end

  # The same pda object can be used on different input tapes.
  # Must always reset the state and stack.
  def feed_tape(input)
    @tape = Tape.new input
    @state = @start_state
    @stack = []
  end

  def execute_transitions
    a=0
    while
      @tape.shift_head

      state_inst = @transition_relation.select {|trans| trans[0] == @state }
      transition = state_inst.detect(ifnone=lambda {break}) do |trans|
        send(trans[1], @tape.head) && trans[2] == :mpty
      end
      puts transition.inspect

      @stack.push @tape.head if transition[4] == :y
      @stack.push @tape.head if transition[4] == :yy
      @state = transition[3]
      a=1
    end
    crash
  end

  private

  def eot(unused)
    @tape.end?
  end

  def input_alphabet_has(char)
    # call the lambda where alphabet defined by construction
    return @input_alphabet.(char) if @input_alphabet.class == Proc
    @input_alphabet.include? char
  end
  alias_method :x, :input_alphabet_has

  # include? will only search keys if called on a hash
  def stack_alphabet_has(char)
    # call the lambda where alphabet defined by construction
    return @stack_alphabet.(char) if @stack_alphabet.class == Proc
    @stack_alphabet.include? char
  end
  alias_method :y, :stack_alphabet_has

  def stack_matches?(char)
    #return false if @stack.empty?
    match_from_stack = @stack_alphabet[top_of_stack]
    return false if match_from_stack.nil?
    return true if match_from_stack == char
    return false
  end
  alias_method :yp, :stack_matches?

  # States:
  #   1. end of tape and stack  (accepting)
  #   2. left delim             y, ⊥/y
  #   3. ascii (not right)      x, ⊥/λ
  #   4. not ascii              (crashing)
  #  (5.) right delim?          (crashing)
  #
  def q0
    @state = :q0
    @tape.shift_head

    if (@accepting_states.include? @state) &&
        @tape.end? && @stack.empty?
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

  # States:
  #   1. end of tape & stack  λ, ⊥/λ
  #   2. left delim           y, z/yz    where z is some delim, not empty
  #   3. right delim          y', y/λ
  #   4. ascii                x, y/y
  #   5. not ascii            (crashing)
  #   6. right with wrong left(crashing)
  #  (7.) right with no left  (crashing)
  #   8. end of tape          (crashing)
  def q1
    @state = :q1
    @tape.shift_head

    # y, z/yz     where z is some delim, not empty
    if @stack_alphabet.include? @tape.head
      # stack was empty
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
    # FIXME #ascii_only? only works on strings.
    # If stack is not empty too, this could run.
    # Also should only run if stack is not empty,
    # but #ascii_only? still can't fail
    if char_is_ascii?
      return q1
    end

    crash
  end

  def halt
    # (accepting)
    # From wikipedia -- 2 modes of accepting:
    #   by final state
    #   by empty stack
    #if @tape.end? && @stack.empty?
    if @accepting_states.include? @state && @tape.end? && @stack.empty?
      puts 'ACCEPT'
      puts "    Halted in state #{@state.to_s}."
      return true
    end

    crash
  end

  # halt, crash or reject
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
    # if tape.head is nil OR input_tape.eof?
    return false if @tape.end?
    # Right matching symbols, y', is part of the input alphabet however we
    # cannot consider it valid criteria for transition.
    return false if @match_alphabet.include? @tape.head
    @tape.head.ascii_only?
  end

  # should pop, not read
  # follow up with a push
  def top_of_stack
    #return @start_stack_symbol if @stack.empty?
    @stack.last
  end
end
