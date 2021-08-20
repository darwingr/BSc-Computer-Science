{- file: p-assig2.hs
 -
 - PDA -- pushdown deterministic automata
 - This program which accepts one line of text (or one file if you prefer) and
 - determines if all of its delimiters are matching.
 - If no match, it indicates where the mistake is first noticed
 - and what was expected.
 -
 - Alphabet
 - 𝚺 = ASCII character set
 -
 - Stack alphabet
 - 𝚪 = {'(', '<', '[', '{'}
 -
 - let x be wildcard for input alphabet
 - let y,z be wildcards for stack symbol
 - let y' be matching close for an open delimiter y
 -}

import System.IO
import Data.Char
-- Initial state & final state
--q0 :: A -> B
q0 stack  = do
  let stack_alphabet = {'(', '<', '[', '{'}
  if 

q1 :: B -> C
q0 b = 

findKey :: (Eq k) => k -> [(k,v)] -> Maybe v
findKey key [] 

main :: IO ()
main = do
  q0 []
