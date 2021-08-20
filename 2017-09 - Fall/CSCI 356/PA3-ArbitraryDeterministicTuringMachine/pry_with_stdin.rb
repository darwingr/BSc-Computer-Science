#!/usr/bin/env ruby
#
# Can use this to create a pry session despite stdin buffer containing other
# data. e.g. when `./main.rb < file.in`

ARGV.include?('-d') ? debug = true : debug = false

count = 0

loop do
  count += 1
  if (debug && count == 13)
    # create a separate stdin file descriptor needed for live debugger session
    pry_fd_stdin = IO.sysopen "/dev/tty"
    pry_stdin = IO.new(pry_fd_stdin, "r")
    require 'pry'
    Pry.config.input = pry_stdin
    binding.pry
  end
end
