/*
 *  Copyright 2008-2009 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <cusp/convert.h>
#include <cusp/detail/utils.h>

namespace cusp
{

//////////////////
// Constructors //
//////////////////
        
// construct from a different matrix
template <typename IndexType, typename ValueType, class MemorySpace>
template <typename MatrixType>
dia_matrix<IndexType,ValueType,MemorySpace>
    ::dia_matrix(const MatrixType& matrix)
    {
        cusp::convert(matrix, *this);
    }

//////////////////////
// Member Functions //
//////////////////////

// copy a matrix in a different format
template <typename IndexType, typename ValueType, class MemorySpace>
template <typename MatrixType>
    dia_matrix<IndexType,ValueType,MemorySpace>&
    dia_matrix<IndexType,ValueType,MemorySpace>
    ::operator=(const MatrixType& matrix)
    {
        cusp::convert(matrix, *this);
        
        return *this;
    }

///////////////////////////
// Convenience Functions //
///////////////////////////

template <typename IndexType,
          typename Array1,
          typename Array2>
dia_matrix_view<Array1,Array2,IndexType>
make_dia_matrix_view(IndexType num_rows,
                     IndexType num_cols,
                     IndexType num_entries,
                     Array1 diagonal_offsets,
                     Array2 values)
{
  return dia_matrix_view<Array1,Array2,IndexType>
    (num_rows, num_cols, num_entries,
     diagonal_offsets, values);
}

template <typename Array1,
          typename Array2,
          typename IndexType,
          typename ValueType,
          typename MemorySpace>
dia_matrix_view<Array1,Array2,IndexType,ValueType,MemorySpace>
make_dia_matrix_view(const dia_matrix_view<Array1,Array2,IndexType,ValueType,MemorySpace>& m)
{
  return dia_matrix_view<Array1,Array2,IndexType>(m);
}
    
template <typename IndexType, typename ValueType, class MemorySpace>
dia_matrix_view <typename cusp::array1d_view<typename cusp::array1d<IndexType,MemorySpace>::iterator>,
                 typename cusp::array2d_view<typename cusp::array1d_view<typename cusp::array1d<ValueType,MemorySpace>::iterator >, cusp::column_major>,
                 IndexType, ValueType, MemorySpace>
make_dia_matrix_view(dia_matrix<IndexType,ValueType,MemorySpace>& m)
{
  return make_dia_matrix_view
    (m.num_rows, m.num_cols, m.num_entries,
     cusp::make_array1d_view(m.diagonal_offsets),
     cusp::make_array2d_view(m.values));
}

template <typename IndexType, typename ValueType, class MemorySpace>
dia_matrix_view <typename cusp::array1d_view<typename cusp::array1d<IndexType,MemorySpace>::const_iterator>,
                 typename cusp::array2d_view<typename cusp::array1d_view<typename cusp::array1d<ValueType,MemorySpace>::const_iterator >, cusp::column_major>,
                 IndexType, ValueType, MemorySpace>
make_dia_matrix_view(const dia_matrix<IndexType,ValueType,MemorySpace>& m)
{
  return make_dia_matrix_view
    (m.num_rows, m.num_cols, m.num_entries,
     cusp::make_array1d_view(m.diagonal_offsets),
     cusp::make_array2d_view(m.values));
}

} // end namespace cusp

