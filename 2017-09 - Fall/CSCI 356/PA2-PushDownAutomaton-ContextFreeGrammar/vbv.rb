#!/usr/bin/env ruby
#
# vbv.in => "vbv"
# Wanted to check why #ascii_only? won't run on end of file, nil char

STDIN.getc  # v
STDIN.getc  # b
STDIN.getc  # v

blank = STDIN.getc  # \n
puts "=> #{blank}"
puts blank.inspect
puts blank.ascii_only?

blank = STDIN.getc  # nil
puts "=> #{blank}"
puts blank.inspect
puts STDIN.eof?
#puts blank.ascii_only?
