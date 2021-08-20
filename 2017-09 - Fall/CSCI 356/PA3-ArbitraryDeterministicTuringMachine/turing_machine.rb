require './tape'

# An arbitrary deterministic Turing Machine (adtm)
#
# A (one-tape) Turing machine can be formally defined as a 7-tuple:
#   M = (𝑸, 𝚪, 𝑏, 𝚺, 𝜹, q₀, 𝐅)
#
# Has a tape, a head, a state register, a finite table of instructions
#
class TuringMachine
  def initialize(:final_states)
    @blank_char = ' '
    @final_states = final_states
    @instrustion_table
  end

  def feed_tape
  end

  def execute
  end

  private
  def halt
    print "HALT: "
    if (final_states.include? state) && position == 0
      puts "ACCEPT"
    else
      puts "REJECT"
    end
    puts input_string
    return 0
  end
end
