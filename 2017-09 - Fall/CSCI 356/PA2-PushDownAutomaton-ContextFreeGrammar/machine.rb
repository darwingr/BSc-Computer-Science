#! /usr/bin/env ruby
# encoding: UTF-8
#
# file: machine.rb

require './pda'

stack_matches = [')', '>', ']', '}']

𝚪 = ['(', '<', '[', '{'].zip(stack_matches).to_h
𝑸 = [:q0, :q1]
𝚺 = ->(element) {
  element != '' &&              # not end of tape aka not nil...\n too?
  element.ascii_only? &&
  !(𝚪.flatten.include? element) # exclude stack and match alphabet
}
# treat 𝜹 as a set of ordered sets, quintuples, called transitions
𝜹 = [
  [:q0, :y,   :empty, :q1, :y],
  [:q0, :x,   :empty, :q0, :nothing],
  [:q1, :y,   :y,     :q1, :yy],
  [:q1, :yp,  :y,     :q1, :nothing],
  [:q1, :eot, :empty, :q0, :nothing],
  [:q1, :x,   :y,     :q1, :y]
]
q₀ = :q0
𝐙₀ = '⊥'
𝐅 = [:q0]

m = PDA.new(𝑸, 𝚺, 𝚪, 𝜹, q₀, 𝐙₀, 𝐅)
m.feed_tape STDIN
status = m.execute_transitions

puts "\n    Machine halted with status #{status}."
exit 0
