# encoding: UTF-8
#
# file: tape.rb

require 'io/console'

# Responsible for handling the input stream that acts as a tape feed for a PDA.
class Tape
  attr_reader :position

  def initialize(source)
    @source = source
    @head = ''
    # start at position 1, like column 1 in a file
    @position = 0
  end

  # Recognizes '\n' preceeding nil as end.
  # Not same as checking for empty string (lambda character)
  def end?
    @source.eof?
  end

  # Reads the character currently under the tape head
  def head
    return '' if @head.nil?
    @head
  end

  # Always shifts right
  def shift_head
    # if end of tape (file, stdin), set blank
    @head = get_char
    @position += 1
  end

  private

  def get_char
    @source.getc
  end
end
