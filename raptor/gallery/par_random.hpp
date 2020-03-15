// Copyright (c) 2015-2017, RAPtor Developer Team
// License: Simplified BSD, http://opensource.org/licenses/BSD-2-Clause

#ifndef RAPTOR_GALLERY_PARRANDOM_HPP
#define RAPTOR_GALLERY_PARRANDOM_HPP

#include <mpi.h>
#include <float.h>
#include <cmath>
#include <stdlib.h>

#include "core/par_matrix.hpp"
#include "core/types.hpp"

using namespace raptor;

static ParCSRMatrix* par_random(int global_rows, int global_cols, int nnz_per_row)
{
    int rank, num_procs;
    RAPtor_MPI_Comm_rank(RAPtor_MPI_COMM_WORLD, &rank);
    RAPtor_MPI_Comm_size(RAPtor_MPI_COMM_WORLD, &num_procs);

    ParCOOMatrix* A_coo;
    double val = 1.0;
    
    A_coo = new ParCOOMatrix(global_rows, global_cols);
    int local_nnz = nnz_per_row * A_coo->local_num_rows;
    for (int i = 0; i < local_nnz; i++)
    {
        A_coo->add_value(rand() % A_coo->local_num_rows, rand() % global_cols, val);
    }
    A_coo->finalize();

    ParCSRMatrix* A = A_coo->to_ParCSR();
    delete A_coo;

    return A;

}

#endif
