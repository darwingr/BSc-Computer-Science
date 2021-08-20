def print_tape_head_diagram(tape, state, position)
  top_edge = '+'
  tape.length.times { top_edge.concat '_' }#; top_edge.concat '+'
  $stderr.puts top_edge
  $stderr.print '|'; $stderr.print tape; $stderr.puts #'|'
  bottom_edge = '+'; position.times { bottom_edge.concat '‾' }
  bottom_edge.concat '↑'
  (tape.length - position - 1).times { bottom_edge.concat '‾' }
  #bottom_edge.concat '+'
  $stderr.puts bottom_edge
  state_line = ' '
  (position-1).times { state_line.concat ' ' }
  state_line.concat "q#{state}"
  $stderr.puts state_line
end
