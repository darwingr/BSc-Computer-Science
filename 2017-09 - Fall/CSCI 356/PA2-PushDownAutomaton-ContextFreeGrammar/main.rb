#! /usr/bin/env ruby
# encoding: UTF-8
#
# file: main.rb

require './delimiter_matcher'

m = DelimiterMatcher.new
m.feed_tape STDIN
status = m.execute_transitions

puts "\n    Machine halted with status #{status}."
exit 0
