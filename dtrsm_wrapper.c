/*
 * Copyright (c) 2010-2020 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2013      Inria. All rights reserved.
 * $COPYRIGHT
 *
 * @generated d Mon May 11 22:42:39 2020
 *
 */

#include "dplasma.h"
#include "dplasma/types.h"
#include "dplasmaaux.h"

#include "dtrsm_LLN.h"
#include "dtrsm_LLT.h"
#include "dtrsm_LUN.h"
#include "dtrsm_LUT.h"
#include "dtrsm_RLN.h"
#include "dtrsm_RLT.h"
#include "dtrsm_RUN.h"
#include "dtrsm_RUT.h"

/**
 *******************************************************************************
 *
 * @ingroup dplasma_double
 *
 *  dplasma_dtrsm_New - Generates parsec taskpool to compute triangular solve
 *     op( A ) * X = B or X * op( A ) = B
 *  WARNING: The computations are not done by this call.
 *
 *******************************************************************************
 *
 * @param[in] side
 *          Specifies whether A appears on the left or on the right of X:
 *          = dplasmaLeft:  op( A ) * X = B
 *          = dplasmaRight: X * op( A ) = B
 *
 * @param[in] uplo
 *          Specifies whether the matrix A is upper triangular or lower
 *          triangular:
 *          = dplasmaUpper: Upper triangle of A is stored;
 *          = dplasmaLower: Lower triangle of A is stored.
 *
 * @param[in] trans
 *          Specifies whether the matrix A is transposed, not transposed or
 *          ugate transposed:
 *          = dplasmaNoTrans:   A is transposed;
 *          = dplasmaTrans:     A is not transposed;
 *          = dplasmaTrans: A is ugate transposed.
 *
 * @param[in] diag
 *          Specifies whether or not A is unit triangular:
 *          = dplasmaNonUnit: A is non unit;
 *          = dplasmaUnit:    A us unit.
 *
 * @param[in] alpha
 *          alpha specifies the scalar alpha
 *
 * @param[in] A
 *          Descriptor of the triangular matrix A of size N-by-N.
 *          If uplo = dplasmaUpper, the leading N-by-N upper triangular part of
 *          the array A contains the upper triangular matrix, and the strictly
 *          lower triangular part of A is not referenced. If uplo = dplasmaLower,
 *          the leading N-by-N lower triangular part of the array A contains the
 *          lower triangular matrix, and the strictly upper triangular part of A
 *          is not referenced. If diag = dplasmaUnit, the diagonal elements of A
 *          are also not referenced and are assumed to be 1.
 *
 * @param[in,out] B
 *          Descriptor of the N-by-NRHS right hand side B
 *          On entry, the N-by-NRHS right hand side matrix B.
 *          On exit, if return value = 0, the N-by-NRHS solution matrix X.
 *
 *******************************************************************************
 *
 * @return
 *          \retval NULL if incorrect parameters are given.
 *          \retval The parsec taskpool describing the operation that can be
 *          enqueued in the runtime with parsec_context_add_taskpool(). It, then, needs to be
 *          destroy with dplasma_dtrsm_Destruct();
 *
 *******************************************************************************
 *
 * @sa dplasma_dtrsm
 * @sa dplasma_dtrsm_Destruct
 * @sa dplasma_ctrsm_New
 * @sa dplasma_dtrsm_New
 * @sa dplasma_strsm_New
 *
 ******************************************************************************/
parsec_taskpool_t*
dplasma_dtrsm_New( dplasma_enum_t side,  dplasma_enum_t uplo,
                   dplasma_enum_t trans, dplasma_enum_t diag,
                   double alpha,
                   const parsec_tiled_matrix_dc_t *A,
                   parsec_tiled_matrix_dc_t *B )
{
    parsec_taskpool_t *parsec_trsm = NULL;

    if ( side == dplasmaLeft ) {
        if ( uplo == dplasmaLower ) {
            if ( trans == dplasmaNoTrans ) {
                parsec_trsm = (parsec_taskpool_t*)parsec_dtrsm_LLN_new(
                    side, uplo, trans, diag, alpha,
                    A,
                    B);
            } else { /* trans =! dplasmaNoTrans */
                parsec_trsm = (parsec_taskpool_t*)parsec_dtrsm_LLT_new(
                    side, uplo, trans, diag, alpha,
                    A,
                    B);
            }
        } else { /* uplo = dplasmaUpper */
            if ( trans == dplasmaNoTrans ) {
                parsec_trsm = (parsec_taskpool_t*)parsec_dtrsm_LUN_new(
                    side, uplo, trans, diag, alpha,
                    A,
                    B);
            } else { /* trans =! dplasmaNoTrans */
                parsec_trsm = (parsec_taskpool_t*)parsec_dtrsm_LUT_new(
                    side, uplo, trans, diag, alpha,
                    A,
                    B);
            }
        }
    } else { /* side == dplasmaRight */
        if ( uplo == dplasmaLower ) {
            if ( trans == dplasmaNoTrans ) {
                parsec_trsm = (parsec_taskpool_t*)parsec_dtrsm_RLN_new(
                    side, uplo, trans, diag, alpha,
                    A,
                    B);
            } else { /* trans =! dplasmaNoTrans */
                parsec_trsm = (parsec_taskpool_t*)parsec_dtrsm_RLT_new(
                    side, uplo, trans, diag, alpha,
                    A,
                    B);
            }
        } else { /* uplo = dplasmaUpper */
            if ( trans == dplasmaNoTrans ) {
                parsec_trsm = (parsec_taskpool_t*)parsec_dtrsm_RUN_new(
                    side, uplo, trans, diag, alpha,
                    A,
                    B);
            } else { /* trans =! dplasmaNoTrans */
                parsec_trsm = (parsec_taskpool_t*)parsec_dtrsm_RUT_new(
                    side, uplo, trans, diag, alpha,
                    A,
                    B);
            }
        }
    }

    dplasma_add2arena_tile(((parsec_dtrsm_LLN_taskpool_t*)parsec_trsm)->arenas[PARSEC_dtrsm_LLN_DEFAULT_ARENA],
                           A->mb*A->nb*sizeof(double),
                           PARSEC_ARENA_ALIGNMENT_SSE,
                           parsec_datatype_double_t, A->mb);

    return parsec_trsm;
}

/**
 *******************************************************************************
 *
 * @ingroup dplasma_double
 *
 *  dplasma_dtrsm_Destruct - Free the data structure associated to an taskpool
 *  created with dplasma_dtrsm_New().
 *
 *******************************************************************************
 *
 * @param[in,out] taskpool
 *          On entry, the taskpool to destroy.
 *          On exit, the taskpool cannot be used anymore.
 *
 *******************************************************************************
 *
 * @sa dplasma_dtrsm_New
 * @sa dplasma_dtrsm
 *
 ******************************************************************************/
void
dplasma_dtrsm_Destruct( parsec_taskpool_t *tp )
{
    parsec_dtrsm_LLN_taskpool_t *otrsm = (parsec_dtrsm_LLN_taskpool_t *)tp;

    parsec_matrix_del2arena( otrsm->arenas[PARSEC_dtrsm_LLN_DEFAULT_ARENA] );
    parsec_taskpool_free(tp);
}

/**
 *******************************************************************************
 *
 * @ingroup dplasma_double
 *
 *  dplasma_dtrsm - Computes triangular solve
 *     op( A ) * X = B or X * op( A ) = B
 *
 *******************************************************************************
 *
 * @param[in,out] parsec
 *          The parsec context of the application that will run the operation.
 *
 * @param[in] side
 *          Specifies whether A appears on the left or on the right of X:
 *          = dplasmaLeft:  op( A ) * X = B
 *          = dplasmaRight: X * op( A ) = B
 *
 * @param[in] uplo
 *          Specifies whether the matrix A is upper triangular or lower
 *          triangular:
 *          = dplasmaUpper: Upper triangle of A is stored;
 *          = dplasmaLower: Lower triangle of A is stored.
 *
 * @param[in] trans
 *          Specifies whether the matrix A is transposed, not transposed or
 *          ugate transposed:
 *          = dplasmaNoTrans:   A is transposed;
 *          = dplasmaTrans:     A is not transposed;
 *          = dplasmaTrans: A is ugate transposed.
 *
 * @param[in] diag
 *          Specifies whether or not A is unit triangular:
 *          = dplasmaNonUnit: A is non unit;
 *          = dplasmaUnit:    A us unit.
 *
 * @param[in] alpha
 *          alpha specifies the scalar alpha
 *
 * @param[in] A
 *          Descriptor of the triangular matrix A of size N-by-N.
 *          If uplo = dplasmaUpper, the leading N-by-N upper triangular part of
 *          the array A contains the upper triangular matrix, and the strictly
 *          lower triangular part of A is not referenced. If uplo = dplasmaLower,
 *          the leading N-by-N lower triangular part of the array A contains the
 *          lower triangular matrix, and the strictly upper triangular part of A
 *          is not referenced. If diag = dplasmaUnit, the diagonal elements of A
 *          are also not referenced and are assumed to be 1.
 *
 * @param[in,out] B
 *          Descriptor of the N-by-NRHS right hand side B
 *          On entry, the N-by-NRHS right hand side matrix B.
 *          On exit, if return value = 0, the N-by-NRHS solution matrix X.
 *
 *******************************************************************************
 *
 * @return
 *          \retval -i if the ith parameters is incorrect.
 *          \retval 0 on success.
 *
 *******************************************************************************
 *
 * @sa dplasma_dtrsm_New
 * @sa dplasma_dtrsm_Destruct
 * @sa dplasma_ctrsm
 * @sa dplasma_dtrsm
 * @sa dplasma_strsm
 *
 ******************************************************************************/
int
dplasma_dtrsm( parsec_context_t *parsec,
               dplasma_enum_t side,  dplasma_enum_t uplo,
               dplasma_enum_t trans, dplasma_enum_t diag,
               double alpha,
               const parsec_tiled_matrix_dc_t *A,
               parsec_tiled_matrix_dc_t *B)
{
    parsec_taskpool_t *parsec_dtrsm = NULL;

    /* Check input arguments */
    if (side != dplasmaLeft && side != dplasmaRight) {
        dplasma_error("dplasma_dtrsm", "illegal value of side");
        return -1;
    }
    if (uplo != dplasmaUpper && uplo != dplasmaLower) {
        dplasma_error("dplasma_dtrsm", "illegal value of uplo");
        return -2;
    }
    if (trans != dplasmaTrans && trans != dplasmaNoTrans && trans != dplasmaTrans ) {
        dplasma_error("dplasma_dtrsm", "illegal value of trans");
        return -3;
    }
    if (diag != dplasmaUnit && diag != dplasmaNonUnit) {
        dplasma_error("dplasma_dtrsm", "illegal value of diag");
        return -4;
    }

    if ( (A->m != A->n) ||
         (( side == dplasmaLeft )  && (A->n != B->m)) ||
         (( side == dplasmaRight ) && (A->n != B->n)) ) {
        dplasma_error("dplasma_dtrsm", "illegal matrix A");
        return -6;
    }

    parsec_dtrsm = dplasma_dtrsm_New(side, uplo, trans, diag, alpha, A, B);

    if ( parsec_dtrsm != NULL )
    {
        parsec_context_add_taskpool( parsec, parsec_dtrsm );
        dplasma_wait_until_completion( parsec );
        dplasma_dtrsm_Destruct( parsec_dtrsm );
        return 0;
    }
    else {
        return -101;
    }
}
