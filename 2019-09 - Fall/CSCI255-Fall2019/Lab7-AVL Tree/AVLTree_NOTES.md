
Predecessor node key

:   The next greatest node in value that is less than current node.
    Found as the righmost node in the left subtree.


Successor node key

:   The next leastest node in value that is
    still greater than the current node.
    Found as the leftmost node in the right subtree.

Height of a (sub)tree

:   Number of nodes in a path starting from the root to the leaf of the longest
    branch.

Balance factor of a (sub)tree

:   The difference of the right subtree height and the left subtree height.
    Like so: `tree.bf = tree.right.height - tree.left.height`.

Rotations

:   Right-Rotate on x re-roots the subtree on the x.left child node.
:   Left-Rotate on x re-roots the subtree on the x.right child node.

:   An imbalanced node with a different hand (balance factor sign) for its
    highest subtree than that subtree must first do a rotate on that child
    before rotating on itself.

:   A rotate on a subtree root node goes in the opposite hand direction from its
    highest subtree.


```ruby
def rotate(n)
  if n.r.bf == n.l.bf
    return
  end


end
```
