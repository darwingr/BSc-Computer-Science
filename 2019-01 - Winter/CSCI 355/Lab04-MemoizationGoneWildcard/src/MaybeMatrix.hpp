/* MaybeMatrix.hpp
 * ---------------
 * CSCI 355 Algorithm Analysis
 * Lab 4    Memoization Gone Wildcard!
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, February 26, 2019
 *
 * Purpose: template (interface and implementation) of MaybeMatrix.
 */
#ifndef MAYBEMATRIX_HPP_INCLUDED
#define MAYBEMATRIX_HPP_INCLUDED

#include <vector>
#include <cassert>

/// MaybeMatrix
///
/// An m-by-n matrix (A_mn) where each position maybe contains a value.
/// Position access is indexed starting from 0 by the same form as 'a_ij'
/// where a is the element located in
///     - the i'th row and
///     - the j'th column.
///
/// Uses the Maybe Monad pattern from Haskell in its interface to simplify
/// having to manage 2 matrices and get the assurances from the type system.
///
/// SPACE COMPLEXITY (at construction and thereafter)
///     S(n) = theta( n )   where n = rows x columns
///
///     The implementation relies on the space-efficient specialization of 
///     std::vector<bool>, which uses std::bitset in some implementation.
///     However, this does not bring an asymptotic improvement.
///
/// TIME COMPLEXITY (at construction)
///     T(n) = theta( n )   where n = rows x columns (x construction of type T)
///
///     The implement relies on std::vector, which is linear in this case.
template<typename T>
class MaybeMatrix {
    std::vector< std::vector<bool>> _maybes; // uses a bit-array internally
    std::vector< std::vector<T> >   _matrix;

public:
    /// T(n) = O(m*n)
    MaybeMatrix(int m_rows, int n_columns);

    /// has
    ///     Returns whether the matrix has a value at a given coordinate.
    ///     Out of range queries don't break the semantics so they must be
    ///     defined behaviour thus returning false.
    /// T(n) = O(1)
    /// Usage:
    ///      MaybeMatrix<bool> m(3,3);
    ///      if( m.has(1,1)) ...
    bool has(int row_i, int column_j) const noexcept;

    /// value
    ///     Returns the value stored at the given coordinates.
    ///     Fails if query is out of range or element is empty,
    ///     so always query using has() first.
    /// T(n) = O(1)
    T value(int row_i, int column_j) const;

    /// emplace
    ///     Mutates the matrix at the given coordinates by the inserting the
    ///     given value.
    ///     Fails for impossible negative coordinates.
    ///     Does nothing for flat matrices but fails for out of range access
    ///     for all others.
    /// T(n) = O(1)
    void emplace(int row_i, int column_j, T value);

private:
    // This makes it obvious that there's a bug in the constructor,
    // where there's >0 columns and 0 rows.
    bool is_flat() const;
};

template<typename T> MaybeMatrix<T>::
MaybeMatrix(int m_rows, int n_columns) :
    _maybes(m_rows, std::vector<bool>(n_columns, false) ),
    _matrix(m_rows, std::vector<T>(n_columns) )
{
    assert( (m_rows >= 0 && n_columns >= 0)
                && "m_rows and n_columns must be positive");
}

template<typename T> auto MaybeMatrix<T>::
has(int row_i, int column_j) const noexcept -> bool
{
    // Out of Range: negative should be false
    if (row_i < 0 || column_j < 0)
        return false;
    // Out of Range: greater than should be false
    if (static_cast<std::size_t>(row_i) >= _matrix.size()
            || static_cast<std::size_t>(column_j) >= _matrix.at(0).size())
        return false;
    bool b = _maybes.at(row_i).at(column_j);
    return b;
}

template<typename T> auto MaybeMatrix<T>::
value(int row_i, int column_j) const -> T
{
    return _matrix.at(row_i).at(column_j);
}

template<typename T> auto MaybeMatrix<T>::
emplace(int row_i, int column_j, T value) -> void
{
    assert((row_i >= 0 && column_j >= 0)
            && "i and j must be positive");
    if (!is_flat()) {
        _matrix.at(row_i).at(column_j) = value;
        _maybes.at(row_i).at(column_j) = true;
    }
}

template<typename T> auto MaybeMatrix<T>::
is_flat() const -> bool
{
    return (_matrix.size() == 0 || _matrix.at(0).size() == 0);
}

#endif // MAYBEMATRIX_HPP_INCLUDED
