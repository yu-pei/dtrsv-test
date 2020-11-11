#ifndef _dtrsm_LLT_h_
#define _dtrsm_LLT_h_
#include "parsec.h"
#include "parsec/parsec_internal.h"

BEGIN_C_DECLS
#define PARSEC_dtrsm_LLT_FULL_ARENA    0
#define PARSEC_dtrsm_LLT_VECTOR_ARENA    1
#define PARSEC_dtrsm_LLT_ARENA_INDEX_MIN 2
    typedef struct parsec_dtrsm_LLT_taskpool_s {
    parsec_taskpool_t super;
    /* The list of globals */
    dplasma_enum_t _g_side;
    dplasma_enum_t _g_uplo;
    dplasma_enum_t _g_trans;
    dplasma_enum_t _g_diag;
    double _g_alpha;
    const parsec_tiled_matrix_dc_t *_g_descA /* data descA */ ;
    parsec_tiled_matrix_dc_t *_g_descB /* data descB */ ;
    /* The array of datatypes (FULL,VECTOR and co.) */
    parsec_arena_t **arenas;
    uint32_t arenas_size;
} parsec_dtrsm_LLT_taskpool_t;

extern parsec_dtrsm_LLT_taskpool_t *parsec_dtrsm_LLT_new(dplasma_enum_t _g_side, dplasma_enum_t _g_uplo,
							 dplasma_enum_t _g_trans, dplasma_enum_t _g_diag,
							 double _g_alpha,
							 const parsec_tiled_matrix_dc_t * _g_descA /* data descA */ ,
							 parsec_tiled_matrix_dc_t * _g_descB /* data descB */ );

#if MAX_LOCAL_COUNT < 3		/* number of parameters and locals dgemm */
#error Too many parameters and local variables (3 out of MAX_LOCAL_COUNT) for task dgemm
#endif /* MAX_PARAM_COUNT */
typedef struct __parsec_dtrsm_LLT_dgemm_assignment_s {
    parsec_assignment_t k;
    parsec_assignment_t m;
    parsec_assignment_t n;
    parsec_assignment_t reserved[MAX_LOCAL_COUNT - 3];
} __parsec_dtrsm_LLT_dgemm_parsec_assignment_t;

#if MAX_PARAM_COUNT < 3		/* total number of flows for task dgemm */
#error Too many flows (3 out of MAX_PARAM_COUNT) for task dgemm
#endif /* MAX_PARAM_COUNT */
typedef struct __parsec_dtrsm_LLT_dgemm_data_s {
    parsec_data_pair_t _f_E;
    parsec_data_pair_t _f_C;
    parsec_data_pair_t _f_D;
    parsec_data_pair_t unused[MAX_LOCAL_COUNT - 3];
} __parsec_dtrsm_LLT_dgemm_data_t;

typedef struct __parsec_dtrsm_LLT_dgemm_task_s {
    PARSEC_MINIMAL_EXECUTION_CONTEXT
#if defined(PARSEC_PROF_TRACE)
    parsec_task_prof_info_t prof_info;
#endif				/* defined(PARSEC_PROF_TRACE) */
    struct __parsec_dtrsm_LLT_dgemm_assignment_s locals;
#if defined(PARSEC_SIM)
    int sim_exec_date;
#endif
    struct __parsec_dtrsm_LLT_dgemm_data_s data;
} __parsec_dtrsm_LLT_dgemm_task_t;


#if MAX_LOCAL_COUNT < 1		/* number of parameters and locals write_B0 */
#error Too many parameters and local variables (1 out of MAX_LOCAL_COUNT) for task write_B0
#endif /* MAX_PARAM_COUNT */
typedef struct __parsec_dtrsm_LLT_write_B0_assignment_s {
    parsec_assignment_t k;
    parsec_assignment_t reserved[MAX_LOCAL_COUNT - 1];
} __parsec_dtrsm_LLT_write_B0_parsec_assignment_t;

#if MAX_PARAM_COUNT < 1		/* total number of flows for task write_B0 */
#error Too many flows (1 out of MAX_PARAM_COUNT) for task write_B0
#endif /* MAX_PARAM_COUNT */
typedef struct __parsec_dtrsm_LLT_write_B0_data_s {
    parsec_data_pair_t _f_B;
    parsec_data_pair_t unused[MAX_LOCAL_COUNT - 1];
} __parsec_dtrsm_LLT_write_B0_data_t;

typedef struct __parsec_dtrsm_LLT_write_B0_task_s {
    PARSEC_MINIMAL_EXECUTION_CONTEXT
#if defined(PARSEC_PROF_TRACE)
    parsec_task_prof_info_t prof_info;
#endif				/* defined(PARSEC_PROF_TRACE) */
    struct __parsec_dtrsm_LLT_write_B0_assignment_s locals;
#if defined(PARSEC_SIM)
    int sim_exec_date;
#endif
    struct __parsec_dtrsm_LLT_write_B0_data_s data;
} __parsec_dtrsm_LLT_write_B0_task_t;


#if MAX_LOCAL_COUNT < 1		/* number of parameters and locals read_B0 */
#error Too many parameters and local variables (1 out of MAX_LOCAL_COUNT) for task read_B0
#endif /* MAX_PARAM_COUNT */
typedef struct __parsec_dtrsm_LLT_read_B0_assignment_s {
    parsec_assignment_t k;
    parsec_assignment_t reserved[MAX_LOCAL_COUNT - 1];
} __parsec_dtrsm_LLT_read_B0_parsec_assignment_t;

#if MAX_PARAM_COUNT < 1		/* total number of flows for task read_B0 */
#error Too many flows (1 out of MAX_PARAM_COUNT) for task read_B0
#endif /* MAX_PARAM_COUNT */
typedef struct __parsec_dtrsm_LLT_read_B0_data_s {
    parsec_data_pair_t _f_B;
    parsec_data_pair_t unused[MAX_LOCAL_COUNT - 1];
} __parsec_dtrsm_LLT_read_B0_data_t;

typedef struct __parsec_dtrsm_LLT_read_B0_task_s {
    PARSEC_MINIMAL_EXECUTION_CONTEXT
#if defined(PARSEC_PROF_TRACE)
    parsec_task_prof_info_t prof_info;
#endif				/* defined(PARSEC_PROF_TRACE) */
    struct __parsec_dtrsm_LLT_read_B0_assignment_s locals;
#if defined(PARSEC_SIM)
    int sim_exec_date;
#endif
    struct __parsec_dtrsm_LLT_read_B0_data_s data;
} __parsec_dtrsm_LLT_read_B0_task_t;


#if MAX_LOCAL_COUNT < 2		/* number of parameters and locals dtrsm */
#error Too many parameters and local variables (2 out of MAX_LOCAL_COUNT) for task dtrsm
#endif /* MAX_PARAM_COUNT */
typedef struct __parsec_dtrsm_LLT_dtrsm_assignment_s {
    parsec_assignment_t k;
    parsec_assignment_t n;
    parsec_assignment_t reserved[MAX_LOCAL_COUNT - 2];
} __parsec_dtrsm_LLT_dtrsm_parsec_assignment_t;

#if MAX_PARAM_COUNT < 2		/* total number of flows for task dtrsm */
#error Too many flows (2 out of MAX_PARAM_COUNT) for task dtrsm
#endif /* MAX_PARAM_COUNT */
typedef struct __parsec_dtrsm_LLT_dtrsm_data_s {
    parsec_data_pair_t _f_B;
    parsec_data_pair_t _f_A;
    parsec_data_pair_t unused[MAX_LOCAL_COUNT - 2];
} __parsec_dtrsm_LLT_dtrsm_data_t;

typedef struct __parsec_dtrsm_LLT_dtrsm_task_s {
    PARSEC_MINIMAL_EXECUTION_CONTEXT
#if defined(PARSEC_PROF_TRACE)
    parsec_task_prof_info_t prof_info;
#endif				/* defined(PARSEC_PROF_TRACE) */
    struct __parsec_dtrsm_LLT_dtrsm_assignment_s locals;
#if defined(PARSEC_SIM)
    int sim_exec_date;
#endif
    struct __parsec_dtrsm_LLT_dtrsm_data_s data;
} __parsec_dtrsm_LLT_dtrsm_task_t;


END_C_DECLS
#endif /* _dtrsm_LLT_h_ */
