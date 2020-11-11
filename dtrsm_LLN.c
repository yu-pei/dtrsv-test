#include "parsec.h"
#include "parsec/parsec_internal.h"
#include "parsec/ayudame.h"
#include "parsec/execution_stream.h"
#if defined(PARSEC_HAVE_CUDA)
#include "parsec/mca/device/cuda/device_cuda.h"
#endif /* defined(PARSEC_HAVE_CUDA) */
#include <alloca.h>

#define PARSEC_dtrsm_LLN_NB_TASK_CLASSES 4
#define PARSEC_dtrsm_LLN_NB_DATA 2

typedef struct __parsec_dtrsm_LLN_internal_taskpool_s __parsec_dtrsm_LLN_internal_taskpool_t;
struct parsec_dtrsm_LLN_internal_taskpool_s;

/** Predeclarations of the parsec_task_class_t */
static const parsec_task_class_t dtrsm_LLN_dgemm;
static const parsec_task_class_t dtrsm_LLN_write_B0;
static const parsec_task_class_t dtrsm_LLN_read_B0;
static const parsec_task_class_t dtrsm_LLN_dtrsm;
/** Predeclarations of the parameters */
static const parsec_flow_t flow_of_dtrsm_LLN_dgemm_for_E;
static const parsec_flow_t flow_of_dtrsm_LLN_dgemm_for_C;
static const parsec_flow_t flow_of_dtrsm_LLN_dgemm_for_D;
static const parsec_flow_t flow_of_dtrsm_LLN_dgemm_for_ctl;
static const parsec_flow_t flow_of_dtrsm_LLN_write_B0_for_B;
static const parsec_flow_t flow_of_dtrsm_LLN_read_B0_for_B;
static const parsec_flow_t flow_of_dtrsm_LLN_dtrsm_for_B;
static const parsec_flow_t flow_of_dtrsm_LLN_dtrsm_for_A;
static const parsec_flow_t flow_of_dtrsm_LLN_dtrsm_for_ctl;
#line 2 "dtrsm_LLN.jdf"
/*
 *  Copyright (c) 2010-2020
 *
 *  The University of Tennessee and The University
 *  of Tennessee Research Foundation.  All rights
 *  reserved.
 *
 * @generated d Mon May 11 22:42:41 2020
 *
 */
#include "dplasmajdf.h"
#include "parsec/data_dist/matrix/matrix.h"
//#define DRYRUN 1

#line 47 "dtrsm_LLN.c"
#include "dtrsm_LLN.h"

struct __parsec_dtrsm_LLN_internal_taskpool_s {
    parsec_dtrsm_LLN_taskpool_t super;
    volatile int32_t sync_point;
    parsec_task_t *startup_queue;
    /* The ranges to compute the hash key */
    int dgemm_k_range;
    int dgemm_m_range;
    int dgemm_n_range;
    int write_B0_k_range;
    int read_B0_k_range;
    int dtrsm_k_range;
    int dtrsm_n_range;
    /* The list of data repositories  dgemm  write_B0  read_B0  dtrsm */
    data_repo_t *repositories[4];
};

#if defined(PARSEC_PROF_TRACE)
#if defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
static int dtrsm_LLN_profiling_array[4 * PARSEC_dtrsm_LLN_NB_TASK_CLASSES] = { -1 };	/* 2 pairs (begin, end) per task, times two because each task class has an internal_init task */
#else /* defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
static int dtrsm_LLN_profiling_array[2 * PARSEC_dtrsm_LLN_NB_TASK_CLASSES] = { -1 };	/* 2 pairs (begin, end) per task */
#endif /* defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
#endif /* defined(PARSEC_PROF_TRACE) */
/* Globals */
#define side (__parsec_tp->super._g_side)
#define uplo (__parsec_tp->super._g_uplo)
#define trans (__parsec_tp->super._g_trans)
#define diag (__parsec_tp->super._g_diag)
#define alpha (__parsec_tp->super._g_alpha)
#define descA __parsec_tp->super._g_descA
#define descB __parsec_tp->super._g_descB

static inline int parsec_imin(int a, int b)
{
    return (a <= b) ? a : b;
};

static inline int parsec_imax(int a, int b)
{
    return (a >= b) ? a : b;
};

static inline int32_t dtrsm_LLN_dgemm_inline_c_expr1_line_95(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							     const __parsec_dtrsm_LLN_dgemm_parsec_assignment_t *
							     assignments)
{
    (void) __parsec_tp;
    /* This inline C function was declared in the context of the task dgemm */
    const int k = assignments->k.value;
    (void) k;
    const int m = assignments->m.value;
    (void) m;
    const int n = assignments->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;

    return FLOPS_DGEMM(CLEAN_MB(descB, m), CLEAN_NB(descB, n), descB->mb);
#line 110 "dtrsm_LLN.c"
}

static inline int32_t dtrsm_LLN_dtrsm_inline_c_expr2_line_26(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							     const __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t *
							     assignments)
{
    (void) __parsec_tp;
    /* This inline C function was declared in the context of the task dtrsm */
    const int k = assignments->k.value;
    (void) k;
    const int n = assignments->n.value;
    (void) n;

    (void) k;
    (void) n;

    return FLOPS_DTRSM(side, CLEAN_MB(descB, k), CLEAN_NB(descB, n));
#line 128 "dtrsm_LLN.c"
}

/* Data Access Macros */
#define data_of_descB(descB_d0, descB_d1)  (((parsec_data_collection_t*)__parsec_tp->super._g_descB)->data_of((parsec_data_collection_t*)__parsec_tp->super._g_descB, (descB_d0), (descB_d1)))
#define data_of_descA(descA_d0, descA_d1)  (((parsec_data_collection_t*)__parsec_tp->super._g_descA)->data_of((parsec_data_collection_t*)__parsec_tp->super._g_descA, (descA_d0), (descA_d1)))

#define rank_of_descB(descB_d0, descB_d1)  (((parsec_data_collection_t*)__parsec_tp->super._g_descB)->rank_of((parsec_data_collection_t*)__parsec_tp->super._g_descB, (descB_d0), (descB_d1)))
#define rank_of_descA(descA_d0, descA_d1)  (((parsec_data_collection_t*)__parsec_tp->super._g_descA)->rank_of((parsec_data_collection_t*)__parsec_tp->super._g_descA, (descA_d0), (descA_d1)))

/* Functions Predicates */
#define dgemm_pred(k, m, n) (((parsec_data_collection_t*)(__parsec_tp->super._g_descA))->myrank == rank_of_descA(m, k))
#define write_B0_pred(k) (((parsec_data_collection_t*)(__parsec_tp->super._g_descB))->myrank == rank_of_descB(k, 0))
#define read_B0_pred(k) (((parsec_data_collection_t*)(__parsec_tp->super._g_descB))->myrank == rank_of_descB(k, 0))
#define dtrsm_pred(k, n) (((parsec_data_collection_t*)(__parsec_tp->super._g_descA))->myrank == rank_of_descA(k, k))

/* Data Repositories */
#define dgemm_repo (__parsec_tp->repositories[3])
#define read_B0_repo (__parsec_tp->repositories[1])
#define dtrsm_repo (__parsec_tp->repositories[0])
/* Release dependencies output macro */
#if defined(PARSEC_DEBUG_NOISIER)
#define RELEASE_DEP_OUTPUT(ES, DEPO, TASKO, DEPI, TASKI, RSRC, RDST, DATA)\
  do { \
    char tmp1[128], tmp2[128]; (void)tmp1; (void)tmp2;\
    PARSEC_DEBUG_VERBOSE(20, parsec_debug_output, "thread %d VP %d explore deps from %s:%s to %s:%s (from rank %d to %d) base ptr %p",\
           (NULL != (ES) ? (ES)->th_id : -1), (NULL != (ES) ? (ES)->virtual_process->vp_id : -1),\
           DEPO, parsec_task_snprintf(tmp1, 128, (parsec_task_t*)(TASKO)),\
           DEPI, parsec_task_snprintf(tmp2, 128, (parsec_task_t*)(TASKI)), (RSRC), (RDST), (DATA));\
  } while(0)
#define ACQUIRE_FLOW(TASKI, DEPI, FUNO, DEPO, LOCALS, PTR)\
  do { \
    char tmp1[128], tmp2[128]; (void)tmp1; (void)tmp2;\
    PARSEC_DEBUG_VERBOSE(20, parsec_debug_output, "task %s acquires flow %s from %s %s data ptr %p",\
           parsec_task_snprintf(tmp1, 128, (parsec_task_t*)(TASKI)), (DEPI),\
           (DEPO), parsec_snprintf_assignments(tmp2, 128, (FUNO), (parsec_assignment_t*)(LOCALS)), (PTR));\
  } while(0)
#else
#define RELEASE_DEP_OUTPUT(ES, DEPO, TASKO, DEPI, TASKI, RSRC, RDST, DATA)
#define ACQUIRE_FLOW(TASKI, DEPI, TASKO, DEPO, LOCALS, PTR)
#endif
static inline parsec_key_t __jdf2c_make_key_dgemm(const parsec_taskpool_t * tp, const parsec_assignment_t * as)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (const __parsec_dtrsm_LLN_internal_taskpool_t *) tp;
    __parsec_dtrsm_LLN_dgemm_parsec_assignment_t ascopy, *assignment = &ascopy;
    uintptr_t __parsec_id = 0;
    memcpy(assignment, as, sizeof(__parsec_dtrsm_LLN_dgemm_parsec_assignment_t));
    const int k = assignment->k.value;
    int __jdf2c_k_min = 0;
    const int m = assignment->m.value;
    int __jdf2c_m_min = (k + 1);
    const int n = assignment->n.value;
    int __jdf2c_n_min = 0;
    __parsec_id += (k - __jdf2c_k_min);
    __parsec_id += (m - __jdf2c_m_min) * __parsec_tp->dgemm_k_range;
    __parsec_id += (n - __jdf2c_n_min) * __parsec_tp->dgemm_k_range * __parsec_tp->dgemm_m_range;
    (void) __parsec_tp;
    return (parsec_key_t) __parsec_id;
}

static char *__jdf2c_key_fns_dgemm_key_print(char *buffer, size_t buffer_size, parsec_key_t __parsec_key_,
					     void *user_data)
{
    uint64_t __parsec_key = (uint64_t) (uintptr_t) __parsec_key_;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (__parsec_dtrsm_LLN_internal_taskpool_t *) user_data;
    int k = (__parsec_key) % __parsec_tp->dgemm_k_range;
    __parsec_key = __parsec_key / __parsec_tp->dgemm_k_range;
    int m = (__parsec_key) % __parsec_tp->dgemm_m_range;
    __parsec_key = __parsec_key / __parsec_tp->dgemm_m_range;
    int n = (__parsec_key) % __parsec_tp->dgemm_n_range;
    __parsec_key = __parsec_key / __parsec_tp->dgemm_n_range;
    snprintf(buffer, buffer_size, "dgemm(%d, %d, %d)", k, m, n);
    return buffer;
}

static parsec_key_fn_t __jdf2c_key_fns_dgemm = {
    .key_equal = parsec_hash_table_generic_64bits_key_equal,
    .key_print = __jdf2c_key_fns_dgemm_key_print,
    .key_hash = parsec_hash_table_generic_64bits_key_hash
};

static inline parsec_key_t __jdf2c_make_key_write_B0(const parsec_taskpool_t * tp, const parsec_assignment_t * as)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (const __parsec_dtrsm_LLN_internal_taskpool_t *) tp;
    __parsec_dtrsm_LLN_write_B0_parsec_assignment_t ascopy, *assignment = &ascopy;
    uintptr_t __parsec_id = 0;
    memcpy(assignment, as, sizeof(__parsec_dtrsm_LLN_write_B0_parsec_assignment_t));
    const int k = assignment->k.value;
    int __jdf2c_k_min = 0;
    __parsec_id += (k - __jdf2c_k_min);
    (void) __parsec_tp;
    return (parsec_key_t) __parsec_id;
}

static char *__jdf2c_key_fns_write_B0_key_print(char *buffer, size_t buffer_size, parsec_key_t __parsec_key_,
						void *user_data)
{
    uint64_t __parsec_key = (uint64_t) (uintptr_t) __parsec_key_;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (__parsec_dtrsm_LLN_internal_taskpool_t *) user_data;
    int k = (__parsec_key) % __parsec_tp->write_B0_k_range;
    __parsec_key = __parsec_key / __parsec_tp->write_B0_k_range;
    snprintf(buffer, buffer_size, "write_B0(%d)", k);
    return buffer;
}

static parsec_key_fn_t __jdf2c_key_fns_write_B0 = {
    .key_equal = parsec_hash_table_generic_64bits_key_equal,
    .key_print = __jdf2c_key_fns_write_B0_key_print,
    .key_hash = parsec_hash_table_generic_64bits_key_hash
};

static inline parsec_key_t __jdf2c_make_key_read_B0(const parsec_taskpool_t * tp, const parsec_assignment_t * as)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (const __parsec_dtrsm_LLN_internal_taskpool_t *) tp;
    __parsec_dtrsm_LLN_read_B0_parsec_assignment_t ascopy, *assignment = &ascopy;
    uintptr_t __parsec_id = 0;
    memcpy(assignment, as, sizeof(__parsec_dtrsm_LLN_read_B0_parsec_assignment_t));
    const int k = assignment->k.value;
    int __jdf2c_k_min = 0;
    __parsec_id += (k - __jdf2c_k_min);
    (void) __parsec_tp;
    return (parsec_key_t) __parsec_id;
}

static char *__jdf2c_key_fns_read_B0_key_print(char *buffer, size_t buffer_size, parsec_key_t __parsec_key_,
					       void *user_data)
{
    uint64_t __parsec_key = (uint64_t) (uintptr_t) __parsec_key_;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (__parsec_dtrsm_LLN_internal_taskpool_t *) user_data;
    int k = (__parsec_key) % __parsec_tp->read_B0_k_range;
    __parsec_key = __parsec_key / __parsec_tp->read_B0_k_range;
    snprintf(buffer, buffer_size, "read_B0(%d)", k);
    return buffer;
}

static parsec_key_fn_t __jdf2c_key_fns_read_B0 = {
    .key_equal = parsec_hash_table_generic_64bits_key_equal,
    .key_print = __jdf2c_key_fns_read_B0_key_print,
    .key_hash = parsec_hash_table_generic_64bits_key_hash
};

static inline parsec_key_t __jdf2c_make_key_dtrsm(const parsec_taskpool_t * tp, const parsec_assignment_t * as)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (const __parsec_dtrsm_LLN_internal_taskpool_t *) tp;
    __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t ascopy, *assignment = &ascopy;
    uintptr_t __parsec_id = 0;
    memcpy(assignment, as, sizeof(__parsec_dtrsm_LLN_dtrsm_parsec_assignment_t));
    const int k = assignment->k.value;
    int __jdf2c_k_min = 0;
    const int n = assignment->n.value;
    int __jdf2c_n_min = 0;
    __parsec_id += (k - __jdf2c_k_min);
    __parsec_id += (n - __jdf2c_n_min) * __parsec_tp->dtrsm_k_range;
    (void) __parsec_tp;
    return (parsec_key_t) __parsec_id;
}

static char *__jdf2c_key_fns_dtrsm_key_print(char *buffer, size_t buffer_size, parsec_key_t __parsec_key_,
					     void *user_data)
{
    uint64_t __parsec_key = (uint64_t) (uintptr_t) __parsec_key_;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (__parsec_dtrsm_LLN_internal_taskpool_t *) user_data;
    int k = (__parsec_key) % __parsec_tp->dtrsm_k_range;
    __parsec_key = __parsec_key / __parsec_tp->dtrsm_k_range;
    int n = (__parsec_key) % __parsec_tp->dtrsm_n_range;
    __parsec_key = __parsec_key / __parsec_tp->dtrsm_n_range;
    snprintf(buffer, buffer_size, "dtrsm(%d, %d)", k, n);
    return buffer;
}

static parsec_key_fn_t __jdf2c_key_fns_dtrsm = {
    .key_equal = parsec_hash_table_generic_64bits_key_equal,
    .key_print = __jdf2c_key_fns_dtrsm_key_print,
    .key_hash = parsec_hash_table_generic_64bits_key_hash
};

/******                                    dgemm                                      ******/

static inline int32_t minexpr_of_symb_dtrsm_LLN_dgemm_k_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							    const __parsec_dtrsm_LLN_dgemm_parsec_assignment_t * locals)
{
    (void) __parsec_tp;
    (void) locals;
    return 0;
}

static const parsec_expr_t minexpr_of_symb_dtrsm_LLN_dgemm_k = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) minexpr_of_symb_dtrsm_LLN_dgemm_k_fct}
		      }
};

static inline int maxexpr_of_symb_dtrsm_LLN_dgemm_k_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							const __parsec_dtrsm_LLN_dgemm_parsec_assignment_t * locals)
{
    const int k = locals->k.value;
    (void) k;
    const int m = locals->m.value;
    (void) m;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (descB->mt - 2);
}

static const parsec_expr_t maxexpr_of_symb_dtrsm_LLN_dgemm_k = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) maxexpr_of_symb_dtrsm_LLN_dgemm_k_fct}
		      }
};
static const parsec_symbol_t symb_dtrsm_LLN_dgemm_k = {.name = "k",.context_index = 0,.min =
	&minexpr_of_symb_dtrsm_LLN_dgemm_k,.max = &maxexpr_of_symb_dtrsm_LLN_dgemm_k,.cst_inc = 1,.expr_inc =
	NULL,.flags = 0x0 };

static inline int minexpr_of_symb_dtrsm_LLN_dgemm_m_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							const __parsec_dtrsm_LLN_dgemm_parsec_assignment_t * locals)
{
    const int k = locals->k.value;
    const int m = locals->m.value;
    (void) m;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (k + 1);
}

static const parsec_expr_t minexpr_of_symb_dtrsm_LLN_dgemm_m = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) minexpr_of_symb_dtrsm_LLN_dgemm_m_fct}
		      }
};

static inline int maxexpr_of_symb_dtrsm_LLN_dgemm_m_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							const __parsec_dtrsm_LLN_dgemm_parsec_assignment_t * locals)
{
    const int k = locals->k.value;
    (void) k;
    const int m = locals->m.value;
    (void) m;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (descB->mt - 1);
}

static const parsec_expr_t maxexpr_of_symb_dtrsm_LLN_dgemm_m = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) maxexpr_of_symb_dtrsm_LLN_dgemm_m_fct}
		      }
};
static const parsec_symbol_t symb_dtrsm_LLN_dgemm_m = {.name = "m",.context_index = 1,.min =
	&minexpr_of_symb_dtrsm_LLN_dgemm_m,.max = &maxexpr_of_symb_dtrsm_LLN_dgemm_m,.cst_inc = 1,.expr_inc =
	NULL,.flags = 0x0 };

static inline int32_t expr_of_symb_dtrsm_LLN_dgemm_n_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							 const __parsec_dtrsm_LLN_dgemm_parsec_assignment_t * locals)
{
    (void) __parsec_tp;
    (void) locals;
    return 0;
}

static const parsec_expr_t expr_of_symb_dtrsm_LLN_dgemm_n = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) expr_of_symb_dtrsm_LLN_dgemm_n_fct}
		      }
};
static const parsec_symbol_t symb_dtrsm_LLN_dgemm_n = {.name = "n",.context_index = 2,.min =
	&expr_of_symb_dtrsm_LLN_dgemm_n,.max = &expr_of_symb_dtrsm_LLN_dgemm_n,.cst_inc = 0,.expr_inc = NULL,.flags =
	PARSEC_SYMBOL_IS_STANDALONE };

static inline int affinity_of_dtrsm_LLN_dgemm(__parsec_dtrsm_LLN_dgemm_task_t * this_task, parsec_data_ref_t * ref)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    const int k = this_task->locals.k.value;
    (void) k;
    const int m = this_task->locals.m.value;
    (void) m;
    const int n = this_task->locals.n.value;
    (void) n;

    /* Silent Warnings: should look into predicate to know what variables are usefull */
    (void) k;
    (void) m;
    (void) n;
    ref->dc = (parsec_data_collection_t *) __parsec_tp->super._g_descA;
    /* Compute data key */
    ref->key = ref->dc->data_key(ref->dc, m, k);
    return 1;
}

static inline int32_t property_2_flops_of_dtrsm_LLN_dgemm_as_expr_fct(const __parsec_dtrsm_LLN_internal_taskpool_t *
								      __parsec_tp,
								      const __parsec_dtrsm_LLN_dgemm_parsec_assignment_t
								      * locals)
{
    (void) __parsec_tp;
    (void) locals;
    return dtrsm_LLN_dgemm_inline_c_expr1_line_95(__parsec_tp, locals);
}

static const parsec_expr_t property_2_flops_of_dtrsm_LLN_dgemm_as_expr = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) property_2_flops_of_dtrsm_LLN_dgemm_as_expr_fct}
		      }
};

static const parsec_property_t properties_of_dtrsm_LLN_dgemm[2] = {
    {.name = "flops",.expr = &property_2_flops_of_dtrsm_LLN_dgemm_as_expr},
    {.name = NULL,.expr = NULL}
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep1_atline_106_fct(const
										     __parsec_dtrsm_LLN_internal_taskpool_t
										     * __parsec_tp,
										     const
										     __parsec_dtrsm_LLN_dgemm_parsec_assignment_t
										     * locals)
{
    const int k = locals->k.value;
    const int m = locals->m.value;
    (void) m;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (k >= 1);
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep1_atline_106 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep1_atline_106_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dgemm_for_E_dep1_atline_106 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep1_atline_106,	/* (k >= 1) */
    .ctl_gather_nb = NULL,
    .task_class_id = 3,		/* dtrsm_LLN_dgemm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dgemm_for_E,
    .dep_index = 2,
    .dep_datatype_index = 2,
    .belongs_to = &flow_of_dtrsm_LLN_dgemm_for_E,
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep2_atline_107_fct(const
										     __parsec_dtrsm_LLN_internal_taskpool_t
										     * __parsec_tp,
										     const
										     __parsec_dtrsm_LLN_dgemm_parsec_assignment_t
										     * locals)
{
    const int k = locals->k.value;
    const int m = locals->m.value;
    (void) m;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (0 == k);
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep2_atline_107 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep2_atline_107_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dgemm_for_E_dep2_atline_107 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep2_atline_107,	/* (0 == k) */
    .ctl_gather_nb = NULL,
    .task_class_id = 1,		/* dtrsm_LLN_read_B0 */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_read_B0_for_B,
    .dep_index = 3,
    .dep_datatype_index = 2,
    .belongs_to = &flow_of_dtrsm_LLN_dgemm_for_E,
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep3_atline_108_fct(const
										     __parsec_dtrsm_LLN_internal_taskpool_t
										     * __parsec_tp,
										     const
										     __parsec_dtrsm_LLN_dgemm_parsec_assignment_t
										     * locals)
{
    const int k = locals->k.value;
    (void) k;
    const int m = locals->m.value;
    (void) m;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (m >= (k + 2));
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep3_atline_108 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep3_atline_108_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dgemm_for_E_dep3_atline_108 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep3_atline_108,	/* (m >= (k + 2)) */
    .ctl_gather_nb = NULL,
    .task_class_id = 3,		/* dtrsm_LLN_dgemm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dgemm_for_E,
    .dep_index = 0,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_dgemm_for_E,
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep4_atline_109_fct(const
										     __parsec_dtrsm_LLN_internal_taskpool_t
										     * __parsec_tp,
										     const
										     __parsec_dtrsm_LLN_dgemm_parsec_assignment_t
										     * locals)
{
    const int k = locals->k.value;
    (void) k;
    const int m = locals->m.value;
    (void) m;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return ((k + 1) == m);
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep4_atline_109 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep4_atline_109_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dgemm_for_E_dep4_atline_109 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_E_dep4_atline_109,	/* ((k + 1) == m) */
    .ctl_gather_nb = NULL,
    .task_class_id = 0,		/* dtrsm_LLN_dtrsm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dtrsm_for_B,
    .dep_index = 1,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_dgemm_for_E,
};

#if MAX_DEP_IN_COUNT < 2	/* number of input dependencies */
#error Too many input dependencies (supports up to MAX_DEP_IN_COUNT [=10] but found 2). Fix the code or recompile PaRSEC with a larger MAX_DEP_IN_COUNT.
#endif
#if MAX_DEP_OUT_COUNT < 2	/* number of output dependencies */
#error Too many output dependencies (supports up to MAX_DEP_OUT_COUNT [=10] but found 2). Fix the code or recompile PaRSEC with a larger MAX_DEP_OUT_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_dgemm_for_E = {
    .name = "E",
    .sym_type = PARSEC_SYM_INOUT,
    .flow_flags = PARSEC_FLOW_ACCESS_RW,
    .flow_index = 0,
    .flow_datatype_mask = 0x1,
    .dep_in = {&flow_of_dtrsm_LLN_dgemm_for_E_dep1_atline_106,
	       &flow_of_dtrsm_LLN_dgemm_for_E_dep2_atline_107},
    .dep_out = {&flow_of_dtrsm_LLN_dgemm_for_E_dep3_atline_108,
		&flow_of_dtrsm_LLN_dgemm_for_E_dep4_atline_109}
};

static parsec_data_t *flow_of_dtrsm_LLN_dgemm_for_C_dep1_atline_103_direct_access(const
										  __parsec_dtrsm_LLN_internal_taskpool_t
										  * __parsec_tp,
										  const
										  __parsec_dtrsm_LLN_dgemm_parsec_assignment_t
										  * assignments)
{
    const int k = assignments->k.value;
    (void) k;
    const int m = assignments->m.value;
    (void) m;
    const int n = assignments->n.value;
    (void) n;

    /* Silence Warnings: should look into parameters to know what variables are useful */
    (void) k;
    (void) m;
    (void) n;
    if (__parsec_tp->super.super.context->my_rank == (int32_t) rank_of_descA(m, k))
	return data_of_descA(m, k);
    return NULL;
}

static const parsec_dep_t flow_of_dtrsm_LLN_dgemm_for_C_dep1_atline_103 = {
    .cond = NULL,		/*  */
    .ctl_gather_nb = NULL,
    .task_class_id = PARSEC_LOCAL_DATA_TASK_CLASS_ID,	/* dtrsm_LLN_descA */
    .direct_data = (parsec_data_lookup_func_t) & flow_of_dtrsm_LLN_dgemm_for_C_dep1_atline_103_direct_access,
    .dep_index = 0,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_dgemm_for_C,
};

#if MAX_DEP_IN_COUNT < 1	/* number of input dependencies */
#error Too many input dependencies (supports up to MAX_DEP_IN_COUNT [=10] but found 1). Fix the code or recompile PaRSEC with a larger MAX_DEP_IN_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_dgemm_for_C = {
    .name = "C",
    .sym_type = PARSEC_SYM_IN,
    .flow_flags = PARSEC_FLOW_ACCESS_READ | PARSEC_FLOW_HAS_IN_DEPS,
    .flow_index = 1,
    .flow_datatype_mask = 0x0,
    .dep_in = {&flow_of_dtrsm_LLN_dgemm_for_C_dep1_atline_103},
    .dep_out = {NULL}
};

static const parsec_dep_t flow_of_dtrsm_LLN_dgemm_for_D_dep1_atline_105 = {
    .cond = NULL,		/*  */
    .ctl_gather_nb = NULL,
    .task_class_id = 0,		/* dtrsm_LLN_dtrsm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dtrsm_for_B,
    .dep_index = 1,
    .dep_datatype_index = 1,
    .belongs_to = &flow_of_dtrsm_LLN_dgemm_for_D,
};

#if MAX_DEP_IN_COUNT < 1	/* number of input dependencies */
#error Too many input dependencies (supports up to MAX_DEP_IN_COUNT [=10] but found 1). Fix the code or recompile PaRSEC with a larger MAX_DEP_IN_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_dgemm_for_D = {
    .name = "D",
    .sym_type = PARSEC_SYM_IN,
    .flow_flags = PARSEC_FLOW_ACCESS_READ,
    .flow_index = 2,
    .flow_datatype_mask = 0x0,
    .dep_in = {&flow_of_dtrsm_LLN_dgemm_for_D_dep1_atline_105},
    .dep_out = {NULL}
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_ctl_dep1_atline_110_fct(const
										       __parsec_dtrsm_LLN_internal_taskpool_t
										       * __parsec_tp,
										       const
										       __parsec_dtrsm_LLN_dgemm_parsec_assignment_t
										       * locals)
{
    const int k = locals->k.value;
    (void) k;
    const int m = locals->m.value;
    (void) m;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) m;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return ((k < 500) && (m > (k + 32)));
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_ctl_dep1_atline_110 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_ctl_dep1_atline_110_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dgemm_for_ctl_dep1_atline_110 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dgemm_for_ctl_dep1_atline_110,	/* ((k < 500) && (m > (k + 32))) */
    .ctl_gather_nb = NULL,
    .task_class_id = 0,		/* dtrsm_LLN_dtrsm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dtrsm_for_ctl,
    .dep_index = 4,
    .dep_datatype_index = 4,
    .belongs_to = &flow_of_dtrsm_LLN_dgemm_for_ctl,
};

#if MAX_DEP_IN_COUNT < 1	/* number of input dependencies */
#error Too many input dependencies (supports up to MAX_DEP_IN_COUNT [=10] but found 1). Fix the code or recompile PaRSEC with a larger MAX_DEP_IN_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_dgemm_for_ctl = {
    .name = "ctl",
    .sym_type = PARSEC_SYM_IN,
    .flow_flags = PARSEC_FLOW_ACCESS_NONE | PARSEC_FLOW_HAS_IN_DEPS,
    .flow_index = 3,
    .flow_datatype_mask = 0x0,
    .dep_in = {&flow_of_dtrsm_LLN_dgemm_for_ctl_dep1_atline_110},
    .dep_out = {NULL}
};

static void
iterate_successors_of_dtrsm_LLN_dgemm(parsec_execution_stream_t * es, const __parsec_dtrsm_LLN_dgemm_task_t * this_task,
				      uint32_t action_mask, parsec_ontask_function_t * ontask, void *ontask_arg)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_task_t nc;		/* generic placeholder for locals */
    parsec_dep_data_description_t data;
    __parsec_dtrsm_LLN_dgemm_parsec_assignment_t __jdf2c__tmp_locals = *(__parsec_dtrsm_LLN_dgemm_parsec_assignment_t *) & this_task->locals;	/* copy of this_task locals in R/W mode to manage local definitions */
    int vpid_dst = -1, rank_src = 0, rank_dst = 0;
    const int k = __jdf2c__tmp_locals.k.value;
    (void) k;
    const int m = __jdf2c__tmp_locals.m.value;
    (void) m;
    const int n = __jdf2c__tmp_locals.n.value;
    (void) n;
    (void) rank_src;
    (void) rank_dst;
    (void) __parsec_tp;
    (void) vpid_dst;
    (void) k;
    (void) m;
    (void) n;
    nc.taskpool = this_task->taskpool;
    nc.priority = this_task->priority;
    nc.chore_id = 0;
#if defined(DISTRIBUTED)
    rank_src = rank_of_descA(m, k);
#endif
    if (action_mask & 0x3) {	/* Flow of data E */
	data.data = this_task->data._f_E.data_out;
	data.arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	data.layout = data.arena->opaque_dtt;
	data.count = 1;
	data.displ = 0;
	if (action_mask & 0x1) {
	    if ((m >= (k + 2))) {
		__parsec_dtrsm_LLN_dgemm_task_t *ncc = (__parsec_dtrsm_LLN_dgemm_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dgemm.task_class_id];
		const int dgemm_k = (k + 1);
		if ((dgemm_k >= (0)) && (dgemm_k <= ((descB->mt - 2)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = dgemm_k;
		    const int dgemm_m = m;
		    if ((dgemm_m >= ((ncc->locals.k.value + 1))) && (dgemm_m <= ((descB->mt - 1)))) {
			assert(&nc.locals[1].value == &ncc->locals.m.value);
			ncc->locals.m.value = dgemm_m;
			const int dgemm_n = n;
			if ((dgemm_n == (0))) {
			    assert(&nc.locals[2].value == &ncc->locals.n.value);
			    ncc->locals.n.value = dgemm_n;
#if defined(DISTRIBUTED)
			    rank_dst = rank_of_descA(ncc->locals.m.value, ncc->locals.k.value);
			    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
				vpid_dst =
				    ((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
				    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA,
					    ncc->locals.m.value, ncc->locals.k.value);
			    nc.priority = __parsec_tp->super.super.priority;
			    RELEASE_DEP_OUTPUT(es, "E", this_task, "E", &nc, rank_src, rank_dst, &data);
			    if (PARSEC_ITERATE_STOP ==
				ontask(es, &nc, (const parsec_task_t *) this_task,
				       &flow_of_dtrsm_LLN_dgemm_for_E_dep3_atline_108, &data, rank_src, rank_dst,
				       vpid_dst, ontask_arg))
				return;
			}
		    }
		}
	    }
	}
	if (action_mask & 0x2) {
	    if (((k + 1) == m)) {
		__parsec_dtrsm_LLN_dtrsm_task_t *ncc = (__parsec_dtrsm_LLN_dtrsm_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dtrsm.task_class_id];
		const int dtrsm_k = m;
		if ((dtrsm_k >= (0)) && (dtrsm_k <= ((descB->mt - 1)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = dtrsm_k;
		    const int dtrsm_n = n;
		    if ((dtrsm_n == (0))) {
			assert(&nc.locals[1].value == &ncc->locals.n.value);
			ncc->locals.n.value = dtrsm_n;
#if defined(DISTRIBUTED)
			rank_dst = rank_of_descA(ncc->locals.k.value, ncc->locals.k.value);
			if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
			    vpid_dst =
				((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
				vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA, ncc->locals.k.value,
					ncc->locals.k.value);
			nc.priority = __parsec_tp->super.super.priority;
			RELEASE_DEP_OUTPUT(es, "E", this_task, "B", &nc, rank_src, rank_dst, &data);
			if (PARSEC_ITERATE_STOP ==
			    ontask(es, &nc, (const parsec_task_t *) this_task,
				   &flow_of_dtrsm_LLN_dgemm_for_E_dep4_atline_109, &data, rank_src, rank_dst, vpid_dst,
				   ontask_arg))
			    return;
		    }
		}
	    }
	}
    }
    /* Flow of data C has only IN dependencies */
    /* Flow of data D has only IN dependencies */
    /* Flow of data ctl has only IN dependencies */
    (void) data;
    (void) nc;
    (void) es;
    (void) ontask;
    (void) ontask_arg;
    (void) rank_dst;
    (void) action_mask;
}

static void
iterate_predecessors_of_dtrsm_LLN_dgemm(parsec_execution_stream_t * es,
					const __parsec_dtrsm_LLN_dgemm_task_t * this_task, uint32_t action_mask,
					parsec_ontask_function_t * ontask, void *ontask_arg)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_task_t nc;		/* generic placeholder for locals */
    parsec_dep_data_description_t data;
    __parsec_dtrsm_LLN_dgemm_parsec_assignment_t __jdf2c__tmp_locals = *(__parsec_dtrsm_LLN_dgemm_parsec_assignment_t *) & this_task->locals;	/* copy of this_task locals in R/W mode to manage local definitions */
    int vpid_dst = -1, rank_src = 0, rank_dst = 0;
    const int k = __jdf2c__tmp_locals.k.value;
    (void) k;
    const int m = __jdf2c__tmp_locals.m.value;
    (void) m;
    const int n = __jdf2c__tmp_locals.n.value;
    (void) n;
    (void) rank_src;
    (void) rank_dst;
    (void) __parsec_tp;
    (void) vpid_dst;
    (void) k;
    (void) m;
    (void) n;
    nc.taskpool = this_task->taskpool;
    nc.priority = this_task->priority;
    nc.chore_id = 0;
#if defined(DISTRIBUTED)
    rank_src = rank_of_descA(m, k);
#endif
    if (action_mask & 0xc) {	/* Flow of data E */
	data.data = this_task->data._f_E.data_out;
	data.arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	data.layout = data.arena->opaque_dtt;
	data.count = 1;
	data.displ = 0;
	if (action_mask & 0x4) {
	    if ((k >= 1)) {
		__parsec_dtrsm_LLN_dgemm_task_t *ncc = (__parsec_dtrsm_LLN_dgemm_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dgemm.task_class_id];
		const int dgemm_k = (k - 1);
		if ((dgemm_k >= (0)) && (dgemm_k <= ((descB->mt - 2)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = dgemm_k;
		    const int dgemm_m = m;
		    if ((dgemm_m >= ((ncc->locals.k.value + 1))) && (dgemm_m <= ((descB->mt - 1)))) {
			assert(&nc.locals[1].value == &ncc->locals.m.value);
			ncc->locals.m.value = dgemm_m;
			const int dgemm_n = n;
			if ((dgemm_n == (0))) {
			    assert(&nc.locals[2].value == &ncc->locals.n.value);
			    ncc->locals.n.value = dgemm_n;
#if defined(DISTRIBUTED)
			    rank_dst = rank_of_descA(ncc->locals.m.value, ncc->locals.k.value);
			    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
				vpid_dst =
				    ((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
				    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA,
					    ncc->locals.m.value, ncc->locals.k.value);
			    nc.priority = __parsec_tp->super.super.priority;
			    RELEASE_DEP_OUTPUT(es, "E", this_task, "E", &nc, rank_src, rank_dst, &data);
			    if (PARSEC_ITERATE_STOP ==
				ontask(es, &nc, (const parsec_task_t *) this_task,
				       &flow_of_dtrsm_LLN_dgemm_for_E_dep1_atline_106, &data, rank_src, rank_dst,
				       vpid_dst, ontask_arg))
				return;
			}
		    }
		}
	    }
	}
	if (action_mask & 0x8) {
	    if ((0 == k)) {
		__parsec_dtrsm_LLN_read_B0_task_t *ncc = (__parsec_dtrsm_LLN_read_B0_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_read_B0.task_class_id];
		const int read_B0_k = m;
		if ((read_B0_k >= (0)) && (read_B0_k <= ((descB->mt - 1)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = read_B0_k;
#if defined(DISTRIBUTED)
		    rank_dst = rank_of_descB(ncc->locals.k.value, 0);
		    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
			vpid_dst =
			    ((parsec_data_collection_t *) __parsec_tp->super._g_descB)->
			    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descB, ncc->locals.k.value, 0);
		    nc.priority = __parsec_tp->super.super.priority;
		    RELEASE_DEP_OUTPUT(es, "E", this_task, "B", &nc, rank_src, rank_dst, &data);
		    if (PARSEC_ITERATE_STOP ==
			ontask(es, &nc, (const parsec_task_t *) this_task,
			       &flow_of_dtrsm_LLN_dgemm_for_E_dep2_atline_107, &data, rank_src, rank_dst, vpid_dst,
			       ontask_arg))
			return;
		}
	    }
	}
    }
    /* Flow of data C has only OUTPUT dependencies to Memory */
    if (action_mask & 0x2) {	/* Flow of data D */
	data.data = this_task->data._f_D.data_out;
	data.arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	data.layout = data.arena->opaque_dtt;
	data.count = 1;
	data.displ = 0;
	if (action_mask & 0x2) {
	    __parsec_dtrsm_LLN_dtrsm_task_t *ncc = (__parsec_dtrsm_LLN_dtrsm_task_t *) & nc;
	    nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dtrsm.task_class_id];
	    const int dtrsm_k = k;
	    if ((dtrsm_k >= (0)) && (dtrsm_k <= ((descB->mt - 1)))) {
		assert(&nc.locals[0].value == &ncc->locals.k.value);
		ncc->locals.k.value = dtrsm_k;
		const int dtrsm_n = n;
		if ((dtrsm_n == (0))) {
		    assert(&nc.locals[1].value == &ncc->locals.n.value);
		    ncc->locals.n.value = dtrsm_n;
#if defined(DISTRIBUTED)
		    rank_dst = rank_of_descA(ncc->locals.k.value, ncc->locals.k.value);
		    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
			vpid_dst =
			    ((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
			    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA, ncc->locals.k.value,
				    ncc->locals.k.value);
		    nc.priority = __parsec_tp->super.super.priority;
		    RELEASE_DEP_OUTPUT(es, "D", this_task, "B", &nc, rank_src, rank_dst, &data);
		    if (PARSEC_ITERATE_STOP ==
			ontask(es, &nc, (const parsec_task_t *) this_task,
			       &flow_of_dtrsm_LLN_dgemm_for_D_dep1_atline_105, &data, rank_src, rank_dst, vpid_dst,
			       ontask_arg))
			return;
		}
	    }
	}
    }
    if (action_mask & 0x10) {	/* Flow of data ctl */
	data.data = this_task->data._f_ctl.data_out;
	data.arena = NULL;
	data.layout = PARSEC_DATATYPE_NULL;
	data.count = /* Control: always empty */ 0;
	data.displ = 0;
	if (action_mask & 0x10) {
	    if (((k < 500) && (m > (k + 32)))) {
		__parsec_dtrsm_LLN_dtrsm_task_t *ncc = (__parsec_dtrsm_LLN_dtrsm_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dtrsm.task_class_id];
		const int dtrsm_k = (k + 1);
		if ((dtrsm_k >= (0)) && (dtrsm_k <= ((descB->mt - 1)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = dtrsm_k;
		    const int dtrsm_n = n;
		    if ((dtrsm_n == (0))) {
			assert(&nc.locals[1].value == &ncc->locals.n.value);
			ncc->locals.n.value = dtrsm_n;
#if defined(DISTRIBUTED)
			rank_dst = rank_of_descA(ncc->locals.k.value, ncc->locals.k.value);
			if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
			    vpid_dst =
				((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
				vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA, ncc->locals.k.value,
					ncc->locals.k.value);
			nc.priority = __parsec_tp->super.super.priority;
			RELEASE_DEP_OUTPUT(es, "ctl", this_task, "ctl", &nc, rank_src, rank_dst, &data);
			if (PARSEC_ITERATE_STOP ==
			    ontask(es, &nc, (const parsec_task_t *) this_task,
				   &flow_of_dtrsm_LLN_dgemm_for_ctl_dep1_atline_110, &data, rank_src, rank_dst,
				   vpid_dst, ontask_arg))
			    return;
		    }
		}
	    }
	}
    }
    (void) data;
    (void) nc;
    (void) es;
    (void) ontask;
    (void) ontask_arg;
    (void) rank_dst;
    (void) action_mask;
}

static int release_deps_of_dtrsm_LLN_dgemm(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dgemm_task_t * this_task,
					   uint32_t action_mask, parsec_remote_deps_t * deps)
{
    PARSEC_PINS(es, RELEASE_DEPS_BEGIN, (parsec_task_t *) this_task); {
	const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	    (const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
	parsec_release_dep_fct_arg_t arg;
	int __vp_id;
	arg.action_mask = action_mask;
	arg.output_usage = 0;
	arg.output_entry = NULL;
#if defined(DISTRIBUTED)
	arg.remote_deps = deps;
#endif /* defined(DISTRIBUTED) */
	assert(NULL != es);
	arg.ready_lists = alloca(sizeof(parsec_task_t *) * es->virtual_process->parsec_context->nb_vp);
	for (__vp_id = 0; __vp_id < es->virtual_process->parsec_context->nb_vp; arg.ready_lists[__vp_id++] = NULL);
	(void) __parsec_tp;
	(void) deps;
	if (action_mask & (PARSEC_ACTION_RELEASE_LOCAL_DEPS | PARSEC_ACTION_GET_REPO_ENTRY)) {
	    arg.output_entry =
		data_repo_lookup_entry_and_create(es, dgemm_repo,
						  __jdf2c_make_key_dgemm((const parsec_taskpool_t *) __parsec_tp,
									 (const parsec_assignment_t *) &this_task->
									 locals));
	    arg.output_entry->generator = (void *) this_task;	/* for AYU */
#if defined(PARSEC_SIM)
	    assert(arg.output_entry->sim_exec_date == 0);
	    arg.output_entry->sim_exec_date = this_task->sim_exec_date;
#endif
	}
	iterate_successors_of_dtrsm_LLN_dgemm(es, this_task, action_mask, parsec_release_dep_fct, &arg);

#if defined(DISTRIBUTED)
	if ((action_mask & PARSEC_ACTION_SEND_REMOTE_DEPS) && (NULL != arg.remote_deps)) {
	    parsec_remote_dep_activate(es, (parsec_task_t *) this_task, arg.remote_deps,
				       arg.remote_deps->outgoing_mask);
	}
#endif

	if (action_mask & PARSEC_ACTION_RELEASE_LOCAL_DEPS) {
	    struct parsec_vp_s **vps = es->virtual_process->parsec_context->virtual_processes;
	    data_repo_entry_addto_usage_limit(dgemm_repo, arg.output_entry->ht_item.key, arg.output_usage);
	    for (__vp_id = 0; __vp_id < es->virtual_process->parsec_context->nb_vp; __vp_id++) {
		if (NULL == arg.ready_lists[__vp_id])
		    continue;
		if (__vp_id == es->virtual_process->vp_id) {
		    __parsec_schedule(es, arg.ready_lists[__vp_id], 0);
		} else {
		    __parsec_schedule(vps[__vp_id]->execution_streams[0], arg.ready_lists[__vp_id], 0);
		}
		arg.ready_lists[__vp_id] = NULL;
	    }
	}
	if (action_mask & PARSEC_ACTION_RELEASE_LOCAL_REFS) {
	    const int k = this_task->locals.k.value;
	    (void) k;
	    const int m = this_task->locals.m.value;
	    (void) m;
	    const int n = this_task->locals.n.value;
	    (void) n;

	    (void) k;
	    (void) m;
	    (void) n;

	    if ((k >= 1)) {
		data_repo_entry_used_once(es, dgemm_repo, this_task->data._f_E.data_repo->ht_item.key);
	    } else if ((0 == k)) {
		data_repo_entry_used_once(es, read_B0_repo, this_task->data._f_E.data_repo->ht_item.key);
	    }
	    if (NULL != this_task->data._f_E.data_in) {
		PARSEC_DATA_COPY_RELEASE(this_task->data._f_E.data_in);
	    }
	    if (NULL != this_task->data._f_C.data_in) {
		PARSEC_DATA_COPY_RELEASE(this_task->data._f_C.data_in);
	    }
	    data_repo_entry_used_once(es, dtrsm_repo, this_task->data._f_D.data_repo->ht_item.key);
	    if (NULL != this_task->data._f_D.data_in) {
		PARSEC_DATA_COPY_RELEASE(this_task->data._f_D.data_in);
	    }
	}
	PARSEC_PINS(es, RELEASE_DEPS_END, (parsec_task_t *) this_task);
    }
    return 0;
}

static int data_lookup_of_dtrsm_LLN_dgemm(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dgemm_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_assignment_t generic_locals[MAX_PARAM_COUNT];	/* generic task locals */
    int target_device = 0;
    (void) target_device;
    (void) __parsec_tp;
    (void) generic_locals;
    (void) es;
    parsec_data_copy_t *chunk = NULL;
    data_repo_entry_t *entry = NULL;
    const int k = this_task->locals.k.value;
    (void) k;
    const int m = this_task->locals.m.value;
    (void) m;
    const int n = this_task->locals.n.value;
    (void) n;
  /** Lookup the input data, and store them in the context if any */
    this_task->data._f_E.data_out = NULL;	/* By default, if nothing matches */

    if (NULL == (chunk = this_task->data._f_E.data_in)) {	/* flow E */
	entry = NULL;
	if ((k >= 1)) {
	    __parsec_dtrsm_LLN_dgemm_parsec_assignment_t *target_locals =
		(__parsec_dtrsm_LLN_dgemm_parsec_assignment_t *) & generic_locals;
	    const int dgemmk = target_locals->k.value = (k - 1);
	    (void) dgemmk;
	    const int dgemmm = target_locals->m.value = m;
	    (void) dgemmm;
	    const int dgemmn = target_locals->n.value = n;
	    (void) dgemmn;
	    entry =
		data_repo_lookup_entry(dgemm_repo,
				       __jdf2c_make_key_dgemm((const parsec_taskpool_t *) __parsec_tp,
							      (const parsec_assignment_t *) target_locals));
	    chunk = entry->data[0];	/* E:dgemm <- E:dgemm */
	    ACQUIRE_FLOW(this_task, "E", &dtrsm_LLN_dgemm, "E", target_locals, chunk);
	    this_task->data._f_E.data_out = chunk;
	} else if ((0 == k)) {
	    __parsec_dtrsm_LLN_read_B0_parsec_assignment_t *target_locals =
		(__parsec_dtrsm_LLN_read_B0_parsec_assignment_t *) & generic_locals;
	    const int read_B0k = target_locals->k.value = m;
	    (void) read_B0k;
	    entry =
		data_repo_lookup_entry(read_B0_repo,
				       __jdf2c_make_key_read_B0((const parsec_taskpool_t *) __parsec_tp,
								(const parsec_assignment_t *) target_locals));
	    chunk = entry->data[0];	/* E:dgemm <- B:read_B0 */
	    ACQUIRE_FLOW(this_task, "E", &dtrsm_LLN_read_B0, "B", target_locals, chunk);
	    this_task->data._f_E.data_out = chunk;
	}
	this_task->data._f_E.data_in = chunk;	/* flow E */
	this_task->data._f_E.data_repo = entry;
    } else {
	this_task->data._f_E.data_out = parsec_data_get_copy(chunk->original, target_device);
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(chunk->original, (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_dgemm_for_E, 0);
#endif
    }
    this_task->data._f_C.data_out = NULL;	/* input only */

    if (NULL == (chunk = this_task->data._f_C.data_in)) {	/* flow C */
	entry = NULL;
	chunk = parsec_data_get_copy(data_of_descA(m, k), target_device);
	PARSEC_OBJ_RETAIN(chunk);
	this_task->data._f_C.data_out = chunk;
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(data_of_descA(m, k), (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_dgemm_for_C,
				       1);
#endif
	this_task->data._f_C.data_in = chunk;	/* flow C */
	this_task->data._f_C.data_repo = entry;
    } else {
	this_task->data._f_C.data_out = parsec_data_get_copy(chunk->original, target_device);
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(chunk->original, (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_dgemm_for_C, 0);
#endif
    }
    this_task->data._f_D.data_out = NULL;	/* input only */

    if (NULL == (chunk = this_task->data._f_D.data_in)) {	/* flow D */
	entry = NULL;
	__parsec_dtrsm_LLN_dtrsm_parsec_assignment_t *target_locals =
	    (__parsec_dtrsm_LLN_dtrsm_parsec_assignment_t *) & generic_locals;
	const int dtrsmk = target_locals->k.value = k;
	(void) dtrsmk;
	const int dtrsmn = target_locals->n.value = n;
	(void) dtrsmn;
	entry =
	    data_repo_lookup_entry(dtrsm_repo,
				   __jdf2c_make_key_dtrsm((const parsec_taskpool_t *) __parsec_tp,
							  (const parsec_assignment_t *) target_locals));
	chunk = entry->data[0];	/* D:dgemm <- B:dtrsm */
	ACQUIRE_FLOW(this_task, "D", &dtrsm_LLN_dtrsm, "B", target_locals, chunk);
	this_task->data._f_D.data_out = chunk;
	this_task->data._f_D.data_in = chunk;	/* flow D */
	this_task->data._f_D.data_repo = entry;
    } else {
	this_task->data._f_D.data_out = parsec_data_get_copy(chunk->original, target_device);
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(chunk->original, (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_dgemm_for_D, 0);
#endif
    }
    /* ctl is a control flow */
    this_task->data._f_ctl.data_in = NULL;
    this_task->data._f_ctl.data_out = NULL;
    this_task->data._f_ctl.data_repo = NULL;
  /** Generate profiling information */
#if defined(PARSEC_PROF_TRACE)
    this_task->prof_info.desc = (parsec_data_collection_t *) __parsec_tp->super._g_descA;
    this_task->prof_info.data_id =
	((parsec_data_collection_t *) __parsec_tp->super._g_descA)->data_key((parsec_data_collection_t *) __parsec_tp->
									     super._g_descA, m, k);
    this_task->prof_info.task_class_id = this_task->task_class->task_class_id;
#endif /* defined(PARSEC_PROF_TRACE) */
    (void) k;
    (void) m;
    (void) n;
    (void) chunk;
    (void) entry;

    return PARSEC_HOOK_RETURN_DONE;
}

static int datatype_lookup_of_dtrsm_LLN_dgemm(parsec_execution_stream_t * es,
					      const __parsec_dtrsm_LLN_dgemm_task_t * this_task, uint32_t * flow_mask,
					      parsec_dep_data_description_t * data)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    (void) __parsec_tp;
    (void) es;
    (void) this_task;
    (void) data;
    const int k = this_task->locals.k.value;
    (void) k;
    const int m = this_task->locals.m.value;
    (void) m;
    const int n = this_task->locals.n.value;
    (void) n;
    if ((*flow_mask) & 0x80000000U) {	/* these are the input flows */
	if ((*flow_mask) & 0x1U) {	/* Flow E */
	    if (((*flow_mask) & 0x1U)
		&& ((k >= 1) || (0 == k))) {
		data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
		data->layout = data->arena->opaque_dtt;
		data->count = 1;
		data->displ = 0;
		(*flow_mask) &= ~0x1U;
		return PARSEC_HOOK_RETURN_NEXT;
	    }
	}			/* (flow_mask & 0x1U) */
	if ((*flow_mask) & 0x2U) {	/* Flow C */
	    if (((*flow_mask) & 0x2U)) {	/* Have unconditional! */
		data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_FULL_ARENA];
		data->layout = data->arena->opaque_dtt;
		data->count = 1;
		data->displ = 0;
		(*flow_mask) &= ~0x2U;
		return PARSEC_HOOK_RETURN_NEXT;
	    }
	}			/* (flow_mask & 0x2U) */
	if ((*flow_mask) & 0x4U) {	/* Flow D */
	    if (((*flow_mask) & 0x4U)) {	/* Have unconditional! */
		data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
		data->layout = data->arena->opaque_dtt;
		data->count = 1;
		data->displ = 0;
		(*flow_mask) &= ~0x4U;
		return PARSEC_HOOK_RETURN_NEXT;
	    }
	}			/* (flow_mask & 0x4U) */
	goto no_mask_match;
    }				/* input flows */
    if ((*flow_mask) & 0x3U) {	/* Flow E */
	if (((*flow_mask) & 0x3U)
	    && ((m >= (k + 2)) || ((k + 1) == m))) {
	    data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	    data->layout = data->arena->opaque_dtt;
	    data->count = 1;
	    data->displ = 0;
	    (*flow_mask) &= ~0x3U;
	    return PARSEC_HOOK_RETURN_NEXT;
	}
    }				/* (flow_mask & 0x3U) */
  no_mask_match:
    data->arena = NULL;
    data->data = NULL;
    data->layout = PARSEC_DATATYPE_NULL;
    data->count = 0;
    data->displ = 0;
    (*flow_mask) = 0;		/* nothing left */
    (void) k;
    (void) m;
    (void) n;
    return PARSEC_HOOK_RETURN_DONE;
}

static int hook_of_dtrsm_LLN_dgemm(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dgemm_task_t * this_task)
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    (void) es;
    (void) __parsec_tp;
    const int k = this_task->locals.k.value;
    (void) k;
    const int m = this_task->locals.m.value;
    (void) m;
    const int n = this_task->locals.n.value;
    (void) n;
    (void) k;
    (void) m;
    (void) n;

  /** Declare the variables that will hold the data, and all the accounting for each */
    parsec_data_copy_t *_f_E = this_task->data._f_E.data_in;
    void *E = PARSEC_DATA_COPY_GET_PTR(_f_E);
    (void) E;
    parsec_data_copy_t *_f_C = this_task->data._f_C.data_in;
    void *C = PARSEC_DATA_COPY_GET_PTR(_f_C);
    (void) C;
    parsec_data_copy_t *_f_D = this_task->data._f_D.data_in;
    void *D = PARSEC_DATA_COPY_GET_PTR(_f_D);
    (void) D;

  /** Update starting simulation date */
#if defined(PARSEC_SIM)
    {
	this_task->sim_exec_date = 0;
	data_repo_entry_t *eE = this_task->data._f_E.data_repo;
	if ((NULL != eE) && (eE->sim_exec_date > this_task->sim_exec_date))
	    this_task->sim_exec_date = eE->sim_exec_date;
	data_repo_entry_t *eC = this_task->data._f_C.data_repo;
	if ((NULL != eC) && (eC->sim_exec_date > this_task->sim_exec_date))
	    this_task->sim_exec_date = eC->sim_exec_date;
	data_repo_entry_t *eD = this_task->data._f_D.data_repo;
	if ((NULL != eD) && (eD->sim_exec_date > this_task->sim_exec_date))
	    this_task->sim_exec_date = eD->sim_exec_date;
	if (this_task->task_class->sim_cost_fct != NULL) {
	    this_task->sim_exec_date += this_task->task_class->sim_cost_fct(this_task);
	}
	if (es->largest_simulation_date < this_task->sim_exec_date)
	    es->largest_simulation_date = this_task->sim_exec_date;
    }
#endif
  /** Transfer the ownership to the CPU */
#if defined(PARSEC_HAVE_CUDA)
    if (NULL != _f_E) {
	parsec_data_transfer_ownership_to_copy(_f_E->original, 0 /* device */ ,
					       PARSEC_FLOW_ACCESS_RW);
    }
#endif /* defined(PARSEC_HAVE_CUDA) */
  /** Cache Awareness Accounting */
#if defined(PARSEC_CACHE_AWARENESS)
    cache_buf_referenced(es->closest_cache, E);
    cache_buf_referenced(es->closest_cache, C);
    cache_buf_referenced(es->closest_cache, D);
#endif /* PARSEC_CACHE_AWARENESS */


#if !defined(PARSEC_PROF_DRY_BODY)

/*-----                                  dgemm BODY                                  -----*/

    PARSEC_TASK_PROF_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id],
			   (parsec_task_t *) this_task);
#line 112 "dtrsm_LLN.jdf"
    {
#ifndef DRYRUN
	double lalpha = ((k) == (0)) ? (alpha) : (double) (1.0);
	int tempmm = ((m) == (descB->mt - 1)) ? (descB->m - (m * descB->mb)) : descB->mb;
	int tempnn = ((n) == (descB->nt - 1)) ? (descB->n - (n * descB->nb)) : descB->nb;
	int lda = BLKLDD(descA, m);
	int ldbk = BLKLDD(descB, k);
	int ldb = BLKLDD(descB, m);

	CORE_dgemm(dplasmaNoTrans, dplasmaNoTrans, tempmm, tempnn, descB->mb, -1., C /* descA(m,k) */ , lda,
		   D /* descB(k,n) */ , ldbk,
		   lalpha, E /* descB(m,n) */ , ldb);
#endif
	printlog("CORE_dgemm(%d, %d, %d)\n"
		 "\t(dplasmaNoTrans, dplasmaNoTrans, tempmm, tempnn, descB->mb, mzone, descA(%d,%d)[%p], lda, descB(%d,%d)[%p], descB->mb, lalpha, descB(%d,%d)[%p], ldb)\n",
		 k, m, n, m, k, C, k, n, D, m, n, E);
    }

#line 1452 "dtrsm_LLN.c"
/*-----                              END OF dgemm BODY                                -----*/



#endif /*!defined(PARSEC_PROF_DRY_BODY) */

    return PARSEC_HOOK_RETURN_DONE;
}

static int complete_hook_of_dtrsm_LLN_dgemm(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dgemm_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
#if defined(DISTRIBUTED)
    const int k = this_task->locals.k.value;
    (void) k;
    const int m = this_task->locals.m.value;
    (void) m;
    const int n = this_task->locals.n.value;
    (void) n;
#endif /* defined(DISTRIBUTED) */
    (void) es;
    (void) __parsec_tp;
    if (NULL != this_task->data._f_E.data_out) {
#if defined(PARSEC_DEBUG_NOISIER)
	char tmp[128];
#endif
	this_task->data._f_E.data_out->version++;	/* E */
	PARSEC_DEBUG_VERBOSE(10, parsec_debug_output,
			     "Complete hook of %s: change Data copy %p to version %d at %s:%d",
			     parsec_task_snprintf(tmp, 128, (parsec_task_t *) (this_task)),
			     this_task->data._f_E.data_out, this_task->data._f_E.data_out->version, __FILE__, __LINE__);
    }
    PARSEC_TASK_PROF_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id + 1],
			   (parsec_task_t *) this_task);
#if defined(DISTRIBUTED)
  /** If not working on distributed, there is no risk that data is not in place */
    (void) k;
    (void) m;
    (void) n;

#endif /* DISTRIBUTED */
#if defined(PARSEC_PROF_GRAPHER)
    parsec_prof_grapher_task((parsec_task_t *) this_task, es->th_id, es->virtual_process->vp_id,
			     __jdf2c_key_fns_dgemm.key_hash(this_task->task_class->
							    make_key((parsec_taskpool_t *) this_task->taskpool,
								     ((parsec_task_t *) this_task)->locals), NULL));
#endif /* defined(PARSEC_PROF_GRAPHER) */
    release_deps_of_dtrsm_LLN_dgemm(es, this_task, PARSEC_ACTION_RELEASE_REMOTE_DEPS | PARSEC_ACTION_RELEASE_LOCAL_DEPS | PARSEC_ACTION_RELEASE_LOCAL_REFS | 0x3,	/* mask of all dep_index */
				    NULL);
    return PARSEC_HOOK_RETURN_DONE;
}

static parsec_hook_return_t release_task_of_dtrsm_LLN_dgemm(parsec_execution_stream_t * es, parsec_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_hash_table_t *ht = (parsec_hash_table_t *) __parsec_tp->super.super.dependencies_array[3];
    parsec_key_t key =
	this_task->task_class->make_key((const parsec_taskpool_t *) __parsec_tp,
					(const parsec_assignment_t *) &this_task->locals);
    parsec_hashable_dependency_t *hash_dep = (parsec_hashable_dependency_t *) parsec_hash_table_remove(ht, key);
    parsec_thread_mempool_free(hash_dep->mempool_owner, hash_dep);
    return parsec_release_task_to_mempool_update_nbtasks(es, this_task);
}

static char *dtrsm_LLN_dtrsm_LLN_dgemm_internal_init_deps_key_functions_key_print(char *buffer, size_t buffer_size,
										  parsec_key_t __parsec_key_,
										  void *user_data)
{
    uint64_t __parsec_key = (uint64_t) (uintptr_t) __parsec_key_;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (__parsec_dtrsm_LLN_internal_taskpool_t *) user_data;
    int k = (__parsec_key) % __parsec_tp->dgemm_k_range;
    __parsec_key = __parsec_key / __parsec_tp->dgemm_k_range;
    int m = (__parsec_key) % __parsec_tp->dgemm_m_range;
    __parsec_key = __parsec_key / __parsec_tp->dgemm_m_range;
    int n = (__parsec_key) % __parsec_tp->dgemm_n_range;
    __parsec_key = __parsec_key / __parsec_tp->dgemm_n_range;
    snprintf(buffer, buffer_size, "dgemm(%d, %d, %d)", k, m, n);
    return buffer;
}

static parsec_key_fn_t dtrsm_LLN_dtrsm_LLN_dgemm_internal_init_deps_key_functions = {
    .key_equal = parsec_hash_table_generic_64bits_key_equal,
    .key_print = dtrsm_LLN_dtrsm_LLN_dgemm_internal_init_deps_key_functions_key_print,
    .key_hash = parsec_hash_table_generic_64bits_key_hash
};

/* Needs: min-max count-tasks iterate */
static int dtrsm_LLN_dgemm_internal_init(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dgemm_task_t * this_task)
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    int32_t nb_tasks = 0, saved_nb_tasks = 0;
    int32_t __k_min = 0x7fffffff, __k_max = 0;
    int32_t __jdf2c_k_min = 0x7fffffff, __jdf2c_k_max = 0;
    int32_t __m_min = 0x7fffffff, __m_max = 0;
    int32_t __jdf2c_m_min = 0x7fffffff, __jdf2c_m_max = 0;
    __parsec_dtrsm_LLN_dgemm_parsec_assignment_t assignments;
    int32_t k, m, n;
    int32_t __jdf2c_k_start, __jdf2c_k_end, __jdf2c_k_inc;
    int32_t __jdf2c_m_start, __jdf2c_m_end, __jdf2c_m_inc;
#if defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
    PARSEC_PROFILING_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id],
			   0, this_task->taskpool->taskpool_id, NULL);
#endif /* defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
    __jdf2c_k_start = 0;
    __jdf2c_k_end = (descB->mt - 2);
    __jdf2c_k_inc = 1;
    __k_min = parsec_imin(__jdf2c_k_start, __jdf2c_k_end);
    __k_max = parsec_imax(__jdf2c_k_start, __jdf2c_k_end);
    __jdf2c_k_min = parsec_imin(__jdf2c_k_min, __k_min);
    __jdf2c_k_max = parsec_imax(__jdf2c_k_max, __k_max);
    for (k = __jdf2c_k_start; k <= __jdf2c_k_end; k += __jdf2c_k_inc) {
	assignments.k.value = k;
	__jdf2c_m_start = (k + 1);
	__jdf2c_m_end = (descB->mt - 1);
	__jdf2c_m_inc = 1;
	__m_min = parsec_imin(__jdf2c_m_start, __jdf2c_m_end);
	__m_max = parsec_imax(__jdf2c_m_start, __jdf2c_m_end);
	__jdf2c_m_min = parsec_imin(__jdf2c_m_min, __m_min);
	__jdf2c_m_max = parsec_imax(__jdf2c_m_max, __m_max);
	for (m = __jdf2c_m_start; m <= __jdf2c_m_end; m += __jdf2c_m_inc) {
	    assignments.m.value = m;
	    {			/* block for the non-range variable n */
		n = 0;
		assignments.n.value = n;
		if (!dgemm_pred(k, m, n))
		    continue;
		nb_tasks++;
	    }			/* block for the non-range variable n */
	}			/* Loop on normal range m */
    }				/* For loop of k */
    if (0 != nb_tasks) {
	(void) parsec_atomic_fetch_add_int32(&__parsec_tp->super.super.nb_tasks, nb_tasks);
    }
    saved_nb_tasks = nb_tasks;
    /* Set the range variables for the collision-free hash-computation */
    __parsec_tp->dgemm_k_range = (__jdf2c_k_max - __jdf2c_k_min) + 1;
    __parsec_tp->dgemm_m_range = (__jdf2c_m_max - __jdf2c_m_min) + 1;
    __parsec_tp->dgemm_n_range = 1;	/* single value, not a range */
    this_task->status = PARSEC_TASK_STATUS_COMPLETE;

    PARSEC_AYU_REGISTER_TASK(&dtrsm_LLN_dgemm);
    __parsec_tp->super.super.dependencies_array[3] = PARSEC_OBJ_NEW(parsec_hash_table_t);
    parsec_hash_table_init(__parsec_tp->super.super.dependencies_array[3],
			   offsetof(parsec_hashable_dependency_t, ht_item), 10,
			   dtrsm_LLN_dtrsm_LLN_dgemm_internal_init_deps_key_functions, this_task->taskpool);
    __parsec_tp->repositories[3] =
	data_repo_create_nothreadsafe(nb_tasks, __jdf2c_key_fns_dgemm, (parsec_taskpool_t *) __parsec_tp, 4);
    (void) saved_nb_tasks;
    (void) __k_min;
    (void) __k_max;
    (void) __m_min;
    (void) __m_max;
    (void) __jdf2c_k_start;
    (void) __jdf2c_k_end;
    (void) __jdf2c_k_inc;
    (void) __jdf2c_m_start;
    (void) __jdf2c_m_end;
    (void) __jdf2c_m_inc;
    (void) assignments;
    (void) __parsec_tp;
    (void) es;
    if (1 == parsec_atomic_fetch_dec_int32(&__parsec_tp->sync_point)) {
	/* Last initialization task complete. Update the number of tasks. */
	nb_tasks = parsec_atomic_fetch_dec_int32(&__parsec_tp->super.super.nb_tasks);
	parsec_mfence();	/* write memory barrier to guarantee that the scheduler gets the correct number of tasks */
	parsec_taskpool_enable((parsec_taskpool_t *) __parsec_tp, &__parsec_tp->startup_queue,
			       (parsec_task_t *) this_task, es, (1 <= nb_tasks));
#if defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
	PARSEC_PROFILING_TRACE(es->es_profile,
			       this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id + 1],
			       0, this_task->taskpool->taskpool_id, NULL);
#endif /* defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
	return PARSEC_HOOK_RETURN_DONE;
    }
    return PARSEC_HOOK_RETURN_DONE;
}

static const __parsec_chore_t __dtrsm_LLN_dgemm_chores[] = {
    {.type = PARSEC_DEV_CPU,
     .evaluate = NULL,
     .hook = (parsec_hook_t *) hook_of_dtrsm_LLN_dgemm},
    {.type = PARSEC_DEV_NONE,
     .evaluate = NULL,
     .hook = (parsec_hook_t *) NULL},	/* End marker */
};

static const parsec_task_class_t dtrsm_LLN_dgemm = {
    .name = "dgemm",
    .task_class_id = 3,
    .nb_flows = 4,
    .nb_parameters = 3,
    .nb_locals = 3,
    .params = {&symb_dtrsm_LLN_dgemm_k, &symb_dtrsm_LLN_dgemm_m, &symb_dtrsm_LLN_dgemm_n, NULL},
    .locals = {&symb_dtrsm_LLN_dgemm_k, &symb_dtrsm_LLN_dgemm_m, &symb_dtrsm_LLN_dgemm_n, NULL},
    .data_affinity = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_dgemm,
    .initial_data = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_dgemm,
    .final_data = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_dgemm,
    .priority = NULL,
    .properties = properties_of_dtrsm_LLN_dgemm,
#if MAX_PARAM_COUNT < 3		/* number of read flows of dgemm */
#error Too many read flows for task dgemm
#endif /* MAX_PARAM_COUNT */
#if MAX_PARAM_COUNT < 1		/* number of write flows of dgemm */
#error Too many write flows for task dgemm
#endif /* MAX_PARAM_COUNT */
    .in =
	{&flow_of_dtrsm_LLN_dgemm_for_E, &flow_of_dtrsm_LLN_dgemm_for_C, &flow_of_dtrsm_LLN_dgemm_for_D,
	 &flow_of_dtrsm_LLN_dgemm_for_ctl, NULL},
    .out = {&flow_of_dtrsm_LLN_dgemm_for_E, NULL},
    .flags = 0x0 | PARSEC_HAS_IN_IN_DEPENDENCIES | PARSEC_USE_DEPS_MASK,
    .dependencies_goal = 0xf,
    .make_key = __jdf2c_make_key_dgemm,
    .key_functions = &__jdf2c_key_fns_dgemm,
    .fini = (parsec_hook_t *) NULL,
    .incarnations = __dtrsm_LLN_dgemm_chores,
    .find_deps = parsec_hash_find_deps,
    .iterate_successors = (parsec_traverse_function_t *) iterate_successors_of_dtrsm_LLN_dgemm,
    .iterate_predecessors = (parsec_traverse_function_t *) iterate_predecessors_of_dtrsm_LLN_dgemm,
    .release_deps = (parsec_release_deps_t *) release_deps_of_dtrsm_LLN_dgemm,
    .prepare_input = (parsec_hook_t *) data_lookup_of_dtrsm_LLN_dgemm,
    .prepare_output = (parsec_hook_t *) NULL,
    .get_datatype = (parsec_datatype_lookup_t *) datatype_lookup_of_dtrsm_LLN_dgemm,
    .complete_execution = (parsec_hook_t *) complete_hook_of_dtrsm_LLN_dgemm,
    .release_task = &release_task_of_dtrsm_LLN_dgemm,
#if defined(PARSEC_SIM)
    .sim_cost_fct = (parsec_sim_cost_fct_t *) NULL,
#endif
};


/******                                    write_B0                                    ******/

static inline int32_t minexpr_of_symb_dtrsm_LLN_write_B0_k_fct(const __parsec_dtrsm_LLN_internal_taskpool_t *
							       __parsec_tp,
							       const __parsec_dtrsm_LLN_write_B0_parsec_assignment_t *
							       locals)
{
    (void) __parsec_tp;
    (void) locals;
    return 0;
}

static const parsec_expr_t minexpr_of_symb_dtrsm_LLN_write_B0_k = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) minexpr_of_symb_dtrsm_LLN_write_B0_k_fct}
		      }
};

static inline int maxexpr_of_symb_dtrsm_LLN_write_B0_k_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							   const __parsec_dtrsm_LLN_write_B0_parsec_assignment_t *
							   locals)
{
    const int k = locals->k.value;
    (void) k;

    (void) k;
    (void) __parsec_tp;
    (void) locals;
    return (descB->mt - 1);
}

static const parsec_expr_t maxexpr_of_symb_dtrsm_LLN_write_B0_k = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) maxexpr_of_symb_dtrsm_LLN_write_B0_k_fct}
		      }
};
static const parsec_symbol_t symb_dtrsm_LLN_write_B0_k = {.name = "k",.context_index = 0,.min =
	&minexpr_of_symb_dtrsm_LLN_write_B0_k,.max = &maxexpr_of_symb_dtrsm_LLN_write_B0_k,.cst_inc = 1,.expr_inc =
	NULL,.flags = 0x0 };

static inline int affinity_of_dtrsm_LLN_write_B0(__parsec_dtrsm_LLN_write_B0_task_t * this_task,
						 parsec_data_ref_t * ref)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    const int k = this_task->locals.k.value;
    (void) k;

    /* Silent Warnings: should look into predicate to know what variables are usefull */
    (void) k;
    ref->dc = (parsec_data_collection_t *) __parsec_tp->super._g_descB;
    /* Compute data key */
    ref->key = ref->dc->data_key(ref->dc, k, 0);
    return 1;
}

static const parsec_property_t properties_of_dtrsm_LLN_write_B0[1] = {
    {.name = NULL,.expr = NULL}
};

static const parsec_dep_t flow_of_dtrsm_LLN_write_B0_for_B_dep1_atline_86 = {
    .cond = NULL,		/*  */
    .ctl_gather_nb = NULL,
    .task_class_id = 0,		/* dtrsm_LLN_dtrsm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dtrsm_for_B,
    .dep_index = 0,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_write_B0_for_B,
};

static parsec_data_t *flow_of_dtrsm_LLN_write_B0_for_B_dep2_atline_87_direct_access(const
										    __parsec_dtrsm_LLN_internal_taskpool_t
										    * __parsec_tp,
										    const
										    __parsec_dtrsm_LLN_write_B0_parsec_assignment_t
										    * assignments)
{
    const int k = assignments->k.value;
    (void) k;

    /* Silence Warnings: should look into parameters to know what variables are useful */
    (void) k;
    if (__parsec_tp->super.super.context->my_rank == (int32_t) rank_of_descB(k, 0))
	return data_of_descB(k, 0);
    return NULL;
}

static const parsec_dep_t flow_of_dtrsm_LLN_write_B0_for_B_dep2_atline_87 = {
    .cond = NULL,		/*  */
    .ctl_gather_nb = NULL,
    .task_class_id = PARSEC_LOCAL_DATA_TASK_CLASS_ID,	/* dtrsm_LLN_descB */
    .direct_data = (parsec_data_lookup_func_t) & flow_of_dtrsm_LLN_write_B0_for_B_dep2_atline_87_direct_access,
    .dep_index = 0,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_write_B0_for_B,
};

#if MAX_DEP_IN_COUNT < 1	/* number of input dependencies */
#error Too many input dependencies (supports up to MAX_DEP_IN_COUNT [=10] but found 1). Fix the code or recompile PaRSEC with a larger MAX_DEP_IN_COUNT.
#endif
#if MAX_DEP_OUT_COUNT < 1	/* number of output dependencies */
#error Too many output dependencies (supports up to MAX_DEP_OUT_COUNT [=10] but found 1). Fix the code or recompile PaRSEC with a larger MAX_DEP_OUT_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_write_B0_for_B = {
    .name = "B",
    .sym_type = PARSEC_SYM_INOUT,
    .flow_flags = PARSEC_FLOW_ACCESS_RW,
    .flow_index = 0,
    .flow_datatype_mask = 0x1,
    .dep_in = {&flow_of_dtrsm_LLN_write_B0_for_B_dep1_atline_86},
    .dep_out = {&flow_of_dtrsm_LLN_write_B0_for_B_dep2_atline_87}
};

static void
iterate_predecessors_of_dtrsm_LLN_write_B0(parsec_execution_stream_t * es,
					   const __parsec_dtrsm_LLN_write_B0_task_t * this_task, uint32_t action_mask,
					   parsec_ontask_function_t * ontask, void *ontask_arg)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_task_t nc;		/* generic placeholder for locals */
    parsec_dep_data_description_t data;
    __parsec_dtrsm_LLN_write_B0_parsec_assignment_t __jdf2c__tmp_locals = *(__parsec_dtrsm_LLN_write_B0_parsec_assignment_t *) & this_task->locals;	/* copy of this_task locals in R/W mode to manage local definitions */
    int vpid_dst = -1, rank_src = 0, rank_dst = 0;
    const int k = __jdf2c__tmp_locals.k.value;
    (void) k;
    (void) rank_src;
    (void) rank_dst;
    (void) __parsec_tp;
    (void) vpid_dst;
    (void) k;
    nc.taskpool = this_task->taskpool;
    nc.priority = this_task->priority;
    nc.chore_id = 0;
#if defined(DISTRIBUTED)
    rank_src = rank_of_descB(k, 0);
#endif
    if (action_mask & 0x1) {	/* Flow of data B */
	data.data = this_task->data._f_B.data_out;
	data.arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	data.layout = data.arena->opaque_dtt;
	data.count = 1;
	data.displ = 0;
	if (action_mask & 0x1) {
	    __parsec_dtrsm_LLN_dtrsm_task_t *ncc = (__parsec_dtrsm_LLN_dtrsm_task_t *) & nc;
	    nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dtrsm.task_class_id];
	    const int dtrsm_k = k;
	    if ((dtrsm_k >= (0)) && (dtrsm_k <= ((descB->mt - 1)))) {
		assert(&nc.locals[0].value == &ncc->locals.k.value);
		ncc->locals.k.value = dtrsm_k;
		const int dtrsm_n = 0;
		if ((dtrsm_n == (0))) {
		    assert(&nc.locals[1].value == &ncc->locals.n.value);
		    ncc->locals.n.value = dtrsm_n;
#if defined(DISTRIBUTED)
		    rank_dst = rank_of_descA(ncc->locals.k.value, ncc->locals.k.value);
		    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
			vpid_dst =
			    ((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
			    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA, ncc->locals.k.value,
				    ncc->locals.k.value);
		    nc.priority = __parsec_tp->super.super.priority;
		    RELEASE_DEP_OUTPUT(es, "B", this_task, "B", &nc, rank_src, rank_dst, &data);
		    if (PARSEC_ITERATE_STOP ==
			ontask(es, &nc, (const parsec_task_t *) this_task,
			       &flow_of_dtrsm_LLN_write_B0_for_B_dep1_atline_86, &data, rank_src, rank_dst, vpid_dst,
			       ontask_arg))
			return;
		}
	    }
	}
    }
    (void) data;
    (void) nc;
    (void) es;
    (void) ontask;
    (void) ontask_arg;
    (void) rank_dst;
    (void) action_mask;
}

static int release_deps_of_dtrsm_LLN_write_B0(parsec_execution_stream_t * es,
					      __parsec_dtrsm_LLN_write_B0_task_t * this_task, uint32_t action_mask,
					      parsec_remote_deps_t * deps)
{
    PARSEC_PINS(es, RELEASE_DEPS_BEGIN, (parsec_task_t *) this_task); {
	const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	    (const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
	parsec_release_dep_fct_arg_t arg;
	int __vp_id;
	arg.action_mask = action_mask;
	arg.output_usage = 0;
	arg.output_entry = NULL;
#if defined(DISTRIBUTED)
	arg.remote_deps = deps;
#endif /* defined(DISTRIBUTED) */
	assert(NULL != es);
	arg.ready_lists = alloca(sizeof(parsec_task_t *) * es->virtual_process->parsec_context->nb_vp);
	for (__vp_id = 0; __vp_id < es->virtual_process->parsec_context->nb_vp; arg.ready_lists[__vp_id++] = NULL);
	(void) __parsec_tp;
	(void) deps;
	/* No successors, don't call iterate_successors and don't release any local deps */
	if (action_mask & PARSEC_ACTION_RELEASE_LOCAL_REFS) {
	    data_repo_entry_used_once(es, dtrsm_repo, this_task->data._f_B.data_repo->ht_item.key);
	    if (NULL != this_task->data._f_B.data_in) {
		PARSEC_DATA_COPY_RELEASE(this_task->data._f_B.data_in);
	    }
	}
	PARSEC_PINS(es, RELEASE_DEPS_END, (parsec_task_t *) this_task);
    }
    return 0;
}

static int data_lookup_of_dtrsm_LLN_write_B0(parsec_execution_stream_t * es,
					     __parsec_dtrsm_LLN_write_B0_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_assignment_t generic_locals[MAX_PARAM_COUNT];	/* generic task locals */
    int target_device = 0;
    (void) target_device;
    (void) __parsec_tp;
    (void) generic_locals;
    (void) es;
    parsec_data_copy_t *chunk = NULL;
    data_repo_entry_t *entry = NULL;
    const int k = this_task->locals.k.value;
    (void) k;
  /** Lookup the input data, and store them in the context if any */
    this_task->data._f_B.data_out = NULL;	/* By default, if nothing matches */

    if (NULL == (chunk = this_task->data._f_B.data_in)) {	/* flow B */
	entry = NULL;
	__parsec_dtrsm_LLN_dtrsm_parsec_assignment_t *target_locals =
	    (__parsec_dtrsm_LLN_dtrsm_parsec_assignment_t *) & generic_locals;
	const int dtrsmk = target_locals->k.value = k;
	(void) dtrsmk;
	const int dtrsmn = target_locals->n.value = 0;
	(void) dtrsmn;
	entry =
	    data_repo_lookup_entry(dtrsm_repo,
				   __jdf2c_make_key_dtrsm((const parsec_taskpool_t *) __parsec_tp,
							  (const parsec_assignment_t *) target_locals));
	chunk = entry->data[0];	/* B:write_B0 <- B:dtrsm */
	ACQUIRE_FLOW(this_task, "B", &dtrsm_LLN_dtrsm, "B", target_locals, chunk);
	this_task->data._f_B.data_out = chunk;
	this_task->data._f_B.data_in = chunk;	/* flow B */
	this_task->data._f_B.data_repo = entry;
    } else {
	this_task->data._f_B.data_out = parsec_data_get_copy(chunk->original, target_device);
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(chunk->original, (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_write_B0_for_B,
				       0);
#endif
    }
  /** Generate profiling information */
#if defined(PARSEC_PROF_TRACE)
    this_task->prof_info.desc = (parsec_data_collection_t *) __parsec_tp->super._g_descB;
    this_task->prof_info.data_id =
	((parsec_data_collection_t *) __parsec_tp->super._g_descB)->data_key((parsec_data_collection_t *) __parsec_tp->
									     super._g_descB, k, 0);
    this_task->prof_info.task_class_id = this_task->task_class->task_class_id;
#endif /* defined(PARSEC_PROF_TRACE) */
    (void) k;
    (void) chunk;
    (void) entry;

    return PARSEC_HOOK_RETURN_DONE;
}

static int datatype_lookup_of_dtrsm_LLN_write_B0(parsec_execution_stream_t * es,
						 const __parsec_dtrsm_LLN_write_B0_task_t * this_task,
						 uint32_t * flow_mask, parsec_dep_data_description_t * data)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    (void) __parsec_tp;
    (void) es;
    (void) this_task;
    (void) data;
    const int k = this_task->locals.k.value;
    (void) k;
    if ((*flow_mask) & 0x80000000U) {	/* these are the input flows */
	if ((*flow_mask) & 0x1U) {	/* Flow B */
	    if (((*flow_mask) & 0x1U)) {	/* Have unconditional! */
		data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
		data->layout = data->arena->opaque_dtt;
		data->count = 1;
		data->displ = 0;
		(*flow_mask) &= ~0x1U;
		return PARSEC_HOOK_RETURN_NEXT;
	    }
	}			/* (flow_mask & 0x1U) */
	goto no_mask_match;
    }				/* input flows */
    if ((*flow_mask) & 0x1U) {	/* Flow B */
	if (((*flow_mask) & 0x1U)) {	/* Have unconditional! */
	    data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	    data->layout = data->arena->opaque_dtt;
	    data->count = 1;
	    data->displ = 0;
	    (*flow_mask) &= ~0x1U;
	    return PARSEC_HOOK_RETURN_NEXT;
	}
    }				/* (flow_mask & 0x1U) */
  no_mask_match:
    data->arena = NULL;
    data->data = NULL;
    data->layout = PARSEC_DATATYPE_NULL;
    data->count = 0;
    data->displ = 0;
    (*flow_mask) = 0;		/* nothing left */
    (void) k;
    return PARSEC_HOOK_RETURN_DONE;
}

static int hook_of_dtrsm_LLN_write_B0(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_write_B0_task_t * this_task)
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    (void) es;
    (void) __parsec_tp;
    const int k = this_task->locals.k.value;
    (void) k;
    (void) k;

  /** Declare the variables that will hold the data, and all the accounting for each */
    parsec_data_copy_t *_f_B = this_task->data._f_B.data_in;
    void *B = PARSEC_DATA_COPY_GET_PTR(_f_B);
    (void) B;

  /** Update starting simulation date */
#if defined(PARSEC_SIM)
    {
	this_task->sim_exec_date = 0;
	data_repo_entry_t *eB = this_task->data._f_B.data_repo;
	if ((NULL != eB) && (eB->sim_exec_date > this_task->sim_exec_date))
	    this_task->sim_exec_date = eB->sim_exec_date;
	if (this_task->task_class->sim_cost_fct != NULL) {
	    this_task->sim_exec_date += this_task->task_class->sim_cost_fct(this_task);
	}
	if (es->largest_simulation_date < this_task->sim_exec_date)
	    es->largest_simulation_date = this_task->sim_exec_date;
    }
#endif
  /** Transfer the ownership to the CPU */
#if defined(PARSEC_HAVE_CUDA)
    if (NULL != _f_B) {
	parsec_data_transfer_ownership_to_copy(_f_B->original, 0 /* device */ ,
					       PARSEC_FLOW_ACCESS_RW);
    }
#endif /* defined(PARSEC_HAVE_CUDA) */
  /** Cache Awareness Accounting */
#if defined(PARSEC_CACHE_AWARENESS)
    cache_buf_referenced(es->closest_cache, B);
#endif /* PARSEC_CACHE_AWARENESS */


#if !defined(PARSEC_PROF_DRY_BODY)

/*-----                                write_B0 BODY                                  -----*/

    PARSEC_TASK_PROF_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id],
			   (parsec_task_t *) this_task);
#line 89 "dtrsm_LLN.jdf"
    {
	/* nothing */
    }

#line 2065 "dtrsm_LLN.c"
/*-----                              END OF write_B0 BODY                              -----*/



#endif /*!defined(PARSEC_PROF_DRY_BODY) */

    return PARSEC_HOOK_RETURN_DONE;
}

static int complete_hook_of_dtrsm_LLN_write_B0(parsec_execution_stream_t * es,
					       __parsec_dtrsm_LLN_write_B0_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
#if defined(DISTRIBUTED)
    const int k = this_task->locals.k.value;
    (void) k;
#endif /* defined(DISTRIBUTED) */
    (void) es;
    (void) __parsec_tp;
    if (NULL != this_task->data._f_B.data_out) {
#if defined(PARSEC_DEBUG_NOISIER)
	char tmp[128];
#endif
	this_task->data._f_B.data_out->version++;	/* B */
	PARSEC_DEBUG_VERBOSE(10, parsec_debug_output,
			     "Complete hook of %s: change Data copy %p to version %d at %s:%d",
			     parsec_task_snprintf(tmp, 128, (parsec_task_t *) (this_task)),
			     this_task->data._f_B.data_out, this_task->data._f_B.data_out->version, __FILE__, __LINE__);
    }
    PARSEC_TASK_PROF_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id + 1],
			   (parsec_task_t *) this_task);
#if defined(DISTRIBUTED)
  /** If not working on distributed, there is no risk that data is not in place */
    if ((NULL != this_task->data._f_B.data_out) && (this_task->data._f_B.data_out->original != data_of_descB(k, 0))) {
	parsec_dep_data_description_t data;
	data.data = this_task->data._f_B.data_out;
	data.arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	data.layout = data.arena->opaque_dtt;
	data.count = 1;
	data.displ = 0;
	assert(data.count > 0);
	parsec_remote_dep_memcpy(es,
				 this_task->taskpool,
				 parsec_data_get_copy(data_of_descB(k, 0), 0), this_task->data._f_B.data_out, &data);
    }
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
    parsec_prof_grapher_data_output((parsec_task_t *) this_task, data_of_descB(k, 0),
				    &flow_of_dtrsm_LLN_write_B0_for_B);
#endif
    (void) k;

#endif /* DISTRIBUTED */
#if defined(PARSEC_PROF_GRAPHER)
    parsec_prof_grapher_task((parsec_task_t *) this_task, es->th_id, es->virtual_process->vp_id,
			     __jdf2c_key_fns_write_B0.key_hash(this_task->task_class->
							       make_key((parsec_taskpool_t *) this_task->taskpool,
									((parsec_task_t *) this_task)->locals), NULL));
#endif /* defined(PARSEC_PROF_GRAPHER) */
    release_deps_of_dtrsm_LLN_write_B0(es, this_task, PARSEC_ACTION_RELEASE_REMOTE_DEPS | PARSEC_ACTION_RELEASE_LOCAL_DEPS | PARSEC_ACTION_RELEASE_LOCAL_REFS | 0x1,	/* mask of all dep_index */
				       NULL);
    return PARSEC_HOOK_RETURN_DONE;
}

static parsec_hook_return_t release_task_of_dtrsm_LLN_write_B0(parsec_execution_stream_t * es,
							       parsec_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_hash_table_t *ht = (parsec_hash_table_t *) __parsec_tp->super.super.dependencies_array[2];
    parsec_key_t key =
	this_task->task_class->make_key((const parsec_taskpool_t *) __parsec_tp,
					(const parsec_assignment_t *) &this_task->locals);
    parsec_hashable_dependency_t *hash_dep = (parsec_hashable_dependency_t *) parsec_hash_table_remove(ht, key);
    parsec_thread_mempool_free(hash_dep->mempool_owner, hash_dep);
    return parsec_release_task_to_mempool_update_nbtasks(es, this_task);
}

static char *dtrsm_LLN_dtrsm_LLN_write_B0_internal_init_deps_key_functions_key_print(char *buffer, size_t buffer_size,
										     parsec_key_t __parsec_key_,
										     void *user_data)
{
    uint64_t __parsec_key = (uint64_t) (uintptr_t) __parsec_key_;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (__parsec_dtrsm_LLN_internal_taskpool_t *) user_data;
    int k = (__parsec_key) % __parsec_tp->write_B0_k_range;
    __parsec_key = __parsec_key / __parsec_tp->write_B0_k_range;
    snprintf(buffer, buffer_size, "write_B0(%d)", k);
    return buffer;
}

static parsec_key_fn_t dtrsm_LLN_dtrsm_LLN_write_B0_internal_init_deps_key_functions = {
    .key_equal = parsec_hash_table_generic_64bits_key_equal,
    .key_print = dtrsm_LLN_dtrsm_LLN_write_B0_internal_init_deps_key_functions_key_print,
    .key_hash = parsec_hash_table_generic_64bits_key_hash
};

/* Needs: min-max count-tasks iterate */
static int dtrsm_LLN_write_B0_internal_init(parsec_execution_stream_t * es,
					    __parsec_dtrsm_LLN_write_B0_task_t * this_task)
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    int32_t nb_tasks = 0, saved_nb_tasks = 0;
    int32_t __k_min = 0x7fffffff, __k_max = 0;
    int32_t __jdf2c_k_min = 0x7fffffff, __jdf2c_k_max = 0;
    __parsec_dtrsm_LLN_write_B0_parsec_assignment_t assignments;
    int32_t k;
    int32_t __jdf2c_k_start, __jdf2c_k_end, __jdf2c_k_inc;
#if defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
    PARSEC_PROFILING_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id],
			   0, this_task->taskpool->taskpool_id, NULL);
#endif /* defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
    __jdf2c_k_start = 0;
    __jdf2c_k_end = (descB->mt - 1);
    __jdf2c_k_inc = 1;
    __k_min = parsec_imin(__jdf2c_k_start, __jdf2c_k_end);
    __k_max = parsec_imax(__jdf2c_k_start, __jdf2c_k_end);
    __jdf2c_k_min = parsec_imin(__jdf2c_k_min, __k_min);
    __jdf2c_k_max = parsec_imax(__jdf2c_k_max, __k_max);
    for (k = __jdf2c_k_start; k <= __jdf2c_k_end; k += __jdf2c_k_inc) {
	assignments.k.value = k;
	if (!write_B0_pred(k))
	    continue;
	nb_tasks++;
    }				/* Loop on normal range k */
    if (0 != nb_tasks) {
	(void) parsec_atomic_fetch_add_int32(&__parsec_tp->super.super.nb_tasks, nb_tasks);
    }
    saved_nb_tasks = nb_tasks;
    /* Set the range variables for the collision-free hash-computation */
    __parsec_tp->write_B0_k_range = (__jdf2c_k_max - __jdf2c_k_min) + 1;
    this_task->status = PARSEC_TASK_STATUS_COMPLETE;

    PARSEC_AYU_REGISTER_TASK(&dtrsm_LLN_write_B0);
    __parsec_tp->super.super.dependencies_array[2] = PARSEC_OBJ_NEW(parsec_hash_table_t);
    parsec_hash_table_init(__parsec_tp->super.super.dependencies_array[2],
			   offsetof(parsec_hashable_dependency_t, ht_item), 10,
			   dtrsm_LLN_dtrsm_LLN_write_B0_internal_init_deps_key_functions, this_task->taskpool);
    __parsec_tp->repositories[2] = NULL;
    (void) saved_nb_tasks;
    (void) __k_min;
    (void) __k_max;
    (void) __jdf2c_k_start;
    (void) __jdf2c_k_end;
    (void) __jdf2c_k_inc;
    (void) assignments;
    (void) __parsec_tp;
    (void) es;
    if (1 == parsec_atomic_fetch_dec_int32(&__parsec_tp->sync_point)) {
	/* Last initialization task complete. Update the number of tasks. */
	nb_tasks = parsec_atomic_fetch_dec_int32(&__parsec_tp->super.super.nb_tasks);
	parsec_mfence();	/* write memory barrier to guarantee that the scheduler gets the correct number of tasks */
	parsec_taskpool_enable((parsec_taskpool_t *) __parsec_tp, &__parsec_tp->startup_queue,
			       (parsec_task_t *) this_task, es, (1 <= nb_tasks));
#if defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
	PARSEC_PROFILING_TRACE(es->es_profile,
			       this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id + 1],
			       0, this_task->taskpool->taskpool_id, NULL);
#endif /* defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
	return PARSEC_HOOK_RETURN_DONE;
    }
    return PARSEC_HOOK_RETURN_DONE;
}

static const __parsec_chore_t __dtrsm_LLN_write_B0_chores[] = {
    {.type = PARSEC_DEV_CPU,
     .evaluate = NULL,
     .hook = (parsec_hook_t *) hook_of_dtrsm_LLN_write_B0},
    {.type = PARSEC_DEV_NONE,
     .evaluate = NULL,
     .hook = (parsec_hook_t *) NULL},	/* End marker */
};

static const parsec_task_class_t dtrsm_LLN_write_B0 = {
    .name = "write_B0",
    .task_class_id = 2,
    .nb_flows = 1,
    .nb_parameters = 1,
    .nb_locals = 1,
    .params = {&symb_dtrsm_LLN_write_B0_k, NULL},
    .locals = {&symb_dtrsm_LLN_write_B0_k, NULL},
    .data_affinity = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_write_B0,
    .initial_data = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_write_B0,
    .final_data = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_write_B0,
    .priority = NULL,
    .properties = properties_of_dtrsm_LLN_write_B0,
#if MAX_PARAM_COUNT < 1		/* number of read flows of write_B0 */
#error Too many read flows for task write_B0
#endif /* MAX_PARAM_COUNT */
#if MAX_PARAM_COUNT < 1		/* number of write flows of write_B0 */
#error Too many write flows for task write_B0
#endif /* MAX_PARAM_COUNT */
    .in = {&flow_of_dtrsm_LLN_write_B0_for_B, NULL},
    .out = {&flow_of_dtrsm_LLN_write_B0_for_B, NULL},
    .flags = 0x0 | PARSEC_USE_DEPS_MASK,
    .dependencies_goal = 0x1,
    .make_key = __jdf2c_make_key_write_B0,
    .key_functions = &__jdf2c_key_fns_write_B0,
    .fini = (parsec_hook_t *) NULL,
    .incarnations = __dtrsm_LLN_write_B0_chores,
    .find_deps = parsec_hash_find_deps,
    .iterate_successors = (parsec_traverse_function_t *) NULL,
    .iterate_predecessors = (parsec_traverse_function_t *) iterate_predecessors_of_dtrsm_LLN_write_B0,
    .release_deps = (parsec_release_deps_t *) release_deps_of_dtrsm_LLN_write_B0,
    .prepare_input = (parsec_hook_t *) data_lookup_of_dtrsm_LLN_write_B0,
    .prepare_output = (parsec_hook_t *) NULL,
    .get_datatype = (parsec_datatype_lookup_t *) datatype_lookup_of_dtrsm_LLN_write_B0,
    .complete_execution = (parsec_hook_t *) complete_hook_of_dtrsm_LLN_write_B0,
    .release_task = &release_task_of_dtrsm_LLN_write_B0,
#if defined(PARSEC_SIM)
    .sim_cost_fct = (parsec_sim_cost_fct_t *) NULL,
#endif
};


/******                                    read_B0                                    ******/

static inline int32_t minexpr_of_symb_dtrsm_LLN_read_B0_k_fct(const __parsec_dtrsm_LLN_internal_taskpool_t *
							      __parsec_tp,
							      const __parsec_dtrsm_LLN_read_B0_parsec_assignment_t *
							      locals)
{
    (void) __parsec_tp;
    (void) locals;
    return 0;
}

static const parsec_expr_t minexpr_of_symb_dtrsm_LLN_read_B0_k = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) minexpr_of_symb_dtrsm_LLN_read_B0_k_fct}
		      }
};

static inline int maxexpr_of_symb_dtrsm_LLN_read_B0_k_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							  const __parsec_dtrsm_LLN_read_B0_parsec_assignment_t * locals)
{
    const int k = locals->k.value;
    (void) k;

    (void) k;
    (void) __parsec_tp;
    (void) locals;
    return (descB->mt - 1);
}

static const parsec_expr_t maxexpr_of_symb_dtrsm_LLN_read_B0_k = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) maxexpr_of_symb_dtrsm_LLN_read_B0_k_fct}
		      }
};
static const parsec_symbol_t symb_dtrsm_LLN_read_B0_k = {.name = "k",.context_index = 0,.min =
	&minexpr_of_symb_dtrsm_LLN_read_B0_k,.max = &maxexpr_of_symb_dtrsm_LLN_read_B0_k,.cst_inc = 1,.expr_inc =
	NULL,.flags = 0x0 };

static inline int affinity_of_dtrsm_LLN_read_B0(__parsec_dtrsm_LLN_read_B0_task_t * this_task, parsec_data_ref_t * ref)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    const int k = this_task->locals.k.value;
    (void) k;

    /* Silent Warnings: should look into predicate to know what variables are usefull */
    (void) k;
    ref->dc = (parsec_data_collection_t *) __parsec_tp->super._g_descB;
    /* Compute data key */
    ref->key = ref->dc->data_key(ref->dc, k, 0);
    return 1;
}

static const parsec_property_t properties_of_dtrsm_LLN_read_B0[1] = {
    {.name = NULL,.expr = NULL}
};

static parsec_data_t *flow_of_dtrsm_LLN_read_B0_for_B_dep1_atline_72_direct_access(const
										   __parsec_dtrsm_LLN_internal_taskpool_t
										   * __parsec_tp,
										   const
										   __parsec_dtrsm_LLN_read_B0_parsec_assignment_t
										   * assignments)
{
    const int k = assignments->k.value;
    (void) k;

    /* Silence Warnings: should look into parameters to know what variables are useful */
    (void) k;
    if (__parsec_tp->super.super.context->my_rank == (int32_t) rank_of_descB(k, 0))
	return data_of_descB(k, 0);
    return NULL;
}

static const parsec_dep_t flow_of_dtrsm_LLN_read_B0_for_B_dep1_atline_72 = {
    .cond = NULL,		/*  */
    .ctl_gather_nb = NULL,
    .task_class_id = PARSEC_LOCAL_DATA_TASK_CLASS_ID,	/* dtrsm_LLN_descB */
    .direct_data = (parsec_data_lookup_func_t) & flow_of_dtrsm_LLN_read_B0_for_B_dep1_atline_72_direct_access,
    .dep_index = 0,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_read_B0_for_B,
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_read_B0_for_B_dep2_atline_73_fct(const
										      __parsec_dtrsm_LLN_internal_taskpool_t
										      * __parsec_tp,
										      const
										      __parsec_dtrsm_LLN_read_B0_parsec_assignment_t
										      * locals)
{
    const int k = locals->k.value;

    (void) k;
    (void) __parsec_tp;
    (void) locals;
    return (k == 0);
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_read_B0_for_B_dep2_atline_73 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_read_B0_for_B_dep2_atline_73_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_read_B0_for_B_dep2_atline_73 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_read_B0_for_B_dep2_atline_73,	/* (k == 0) */
    .ctl_gather_nb = NULL,
    .task_class_id = 0,		/* dtrsm_LLN_dtrsm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dtrsm_for_B,
    .dep_index = 0,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_read_B0_for_B,
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_read_B0_for_B_dep3_atline_74_fct(const
										      __parsec_dtrsm_LLN_internal_taskpool_t
										      * __parsec_tp,
										      const
										      __parsec_dtrsm_LLN_read_B0_parsec_assignment_t
										      * locals)
{
    const int k = locals->k.value;

    (void) k;
    (void) __parsec_tp;
    (void) locals;
    return (k >= 1);
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_read_B0_for_B_dep3_atline_74 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_read_B0_for_B_dep3_atline_74_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_read_B0_for_B_dep3_atline_74 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_read_B0_for_B_dep3_atline_74,	/* (k >= 1) */
    .ctl_gather_nb = NULL,
    .task_class_id = 3,		/* dtrsm_LLN_dgemm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dgemm_for_E,
    .dep_index = 1,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_read_B0_for_B,
};

#if MAX_DEP_IN_COUNT < 1	/* number of input dependencies */
#error Too many input dependencies (supports up to MAX_DEP_IN_COUNT [=10] but found 1). Fix the code or recompile PaRSEC with a larger MAX_DEP_IN_COUNT.
#endif
#if MAX_DEP_OUT_COUNT < 2	/* number of output dependencies */
#error Too many output dependencies (supports up to MAX_DEP_OUT_COUNT [=10] but found 2). Fix the code or recompile PaRSEC with a larger MAX_DEP_OUT_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_read_B0_for_B = {
    .name = "B",
    .sym_type = PARSEC_SYM_INOUT,
    .flow_flags = PARSEC_FLOW_ACCESS_RW | PARSEC_FLOW_HAS_IN_DEPS,
    .flow_index = 0,
    .flow_datatype_mask = 0x1,
    .dep_in = {&flow_of_dtrsm_LLN_read_B0_for_B_dep1_atline_72},
    .dep_out = {&flow_of_dtrsm_LLN_read_B0_for_B_dep2_atline_73,
		&flow_of_dtrsm_LLN_read_B0_for_B_dep3_atline_74}
};

static void
iterate_successors_of_dtrsm_LLN_read_B0(parsec_execution_stream_t * es,
					const __parsec_dtrsm_LLN_read_B0_task_t * this_task, uint32_t action_mask,
					parsec_ontask_function_t * ontask, void *ontask_arg)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_task_t nc;		/* generic placeholder for locals */
    parsec_dep_data_description_t data;
    __parsec_dtrsm_LLN_read_B0_parsec_assignment_t __jdf2c__tmp_locals = *(__parsec_dtrsm_LLN_read_B0_parsec_assignment_t *) & this_task->locals;	/* copy of this_task locals in R/W mode to manage local definitions */
    int vpid_dst = -1, rank_src = 0, rank_dst = 0;
    const int k = __jdf2c__tmp_locals.k.value;
    (void) k;
    (void) rank_src;
    (void) rank_dst;
    (void) __parsec_tp;
    (void) vpid_dst;
    (void) k;
    nc.taskpool = this_task->taskpool;
    nc.priority = this_task->priority;
    nc.chore_id = 0;
#if defined(DISTRIBUTED)
    rank_src = rank_of_descB(k, 0);
#endif
    if (action_mask & 0x3) {	/* Flow of data B */
	data.data = this_task->data._f_B.data_out;
	data.arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	data.layout = data.arena->opaque_dtt;
	data.count = 1;
	data.displ = 0;
	if (action_mask & 0x1) {
	    if ((k == 0)) {
		__parsec_dtrsm_LLN_dtrsm_task_t *ncc = (__parsec_dtrsm_LLN_dtrsm_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dtrsm.task_class_id];
		const int dtrsm_k = k;
		if ((dtrsm_k >= (0)) && (dtrsm_k <= ((descB->mt - 1)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = dtrsm_k;
		    const int dtrsm_n = 0;
		    if ((dtrsm_n == (0))) {
			assert(&nc.locals[1].value == &ncc->locals.n.value);
			ncc->locals.n.value = dtrsm_n;
#if defined(DISTRIBUTED)
			rank_dst = rank_of_descA(ncc->locals.k.value, ncc->locals.k.value);
			if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
			    vpid_dst =
				((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
				vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA, ncc->locals.k.value,
					ncc->locals.k.value);
			nc.priority = __parsec_tp->super.super.priority;
			RELEASE_DEP_OUTPUT(es, "B", this_task, "B", &nc, rank_src, rank_dst, &data);
			if (PARSEC_ITERATE_STOP ==
			    ontask(es, &nc, (const parsec_task_t *) this_task,
				   &flow_of_dtrsm_LLN_read_B0_for_B_dep2_atline_73, &data, rank_src, rank_dst, vpid_dst,
				   ontask_arg))
			    return;
		    }
		}
	    }
	}
	if (action_mask & 0x2) {
	    if ((k >= 1)) {
		__parsec_dtrsm_LLN_dgemm_task_t *ncc = (__parsec_dtrsm_LLN_dgemm_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dgemm.task_class_id];
		const int dgemm_k = 0;
		if ((dgemm_k >= (0)) && (dgemm_k <= ((descB->mt - 2)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = dgemm_k;
		    const int dgemm_m = k;
		    if ((dgemm_m >= ((ncc->locals.k.value + 1))) && (dgemm_m <= ((descB->mt - 1)))) {
			assert(&nc.locals[1].value == &ncc->locals.m.value);
			ncc->locals.m.value = dgemm_m;
			const int dgemm_n = 0;
			if ((dgemm_n == (0))) {
			    assert(&nc.locals[2].value == &ncc->locals.n.value);
			    ncc->locals.n.value = dgemm_n;
#if defined(DISTRIBUTED)
			    rank_dst = rank_of_descA(ncc->locals.m.value, ncc->locals.k.value);
			    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
				vpid_dst =
				    ((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
				    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA,
					    ncc->locals.m.value, ncc->locals.k.value);
			    nc.priority = __parsec_tp->super.super.priority;
			    RELEASE_DEP_OUTPUT(es, "B", this_task, "E", &nc, rank_src, rank_dst, &data);
			    if (PARSEC_ITERATE_STOP ==
				ontask(es, &nc, (const parsec_task_t *) this_task,
				       &flow_of_dtrsm_LLN_read_B0_for_B_dep3_atline_74, &data, rank_src, rank_dst,
				       vpid_dst, ontask_arg))
				return;
			}
		    }
		}
	    }
	}
    }
    (void) data;
    (void) nc;
    (void) es;
    (void) ontask;
    (void) ontask_arg;
    (void) rank_dst;
    (void) action_mask;
}

static int release_deps_of_dtrsm_LLN_read_B0(parsec_execution_stream_t * es,
					     __parsec_dtrsm_LLN_read_B0_task_t * this_task, uint32_t action_mask,
					     parsec_remote_deps_t * deps)
{
    PARSEC_PINS(es, RELEASE_DEPS_BEGIN, (parsec_task_t *) this_task); {
	const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	    (const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
	parsec_release_dep_fct_arg_t arg;
	int __vp_id;
	arg.action_mask = action_mask;
	arg.output_usage = 0;
	arg.output_entry = NULL;
#if defined(DISTRIBUTED)
	arg.remote_deps = deps;
#endif /* defined(DISTRIBUTED) */
	assert(NULL != es);
	arg.ready_lists = alloca(sizeof(parsec_task_t *) * es->virtual_process->parsec_context->nb_vp);
	for (__vp_id = 0; __vp_id < es->virtual_process->parsec_context->nb_vp; arg.ready_lists[__vp_id++] = NULL);
	(void) __parsec_tp;
	(void) deps;
	if (action_mask & (PARSEC_ACTION_RELEASE_LOCAL_DEPS | PARSEC_ACTION_GET_REPO_ENTRY)) {
	    arg.output_entry =
		data_repo_lookup_entry_and_create(es, read_B0_repo,
						  __jdf2c_make_key_read_B0((const parsec_taskpool_t *) __parsec_tp,
									   (const parsec_assignment_t *) &this_task->
									   locals));
	    arg.output_entry->generator = (void *) this_task;	/* for AYU */
#if defined(PARSEC_SIM)
	    assert(arg.output_entry->sim_exec_date == 0);
	    arg.output_entry->sim_exec_date = this_task->sim_exec_date;
#endif
	}
	iterate_successors_of_dtrsm_LLN_read_B0(es, this_task, action_mask, parsec_release_dep_fct, &arg);

#if defined(DISTRIBUTED)
	if ((action_mask & PARSEC_ACTION_SEND_REMOTE_DEPS) && (NULL != arg.remote_deps)) {
	    parsec_remote_dep_activate(es, (parsec_task_t *) this_task, arg.remote_deps,
				       arg.remote_deps->outgoing_mask);
	}
#endif

	if (action_mask & PARSEC_ACTION_RELEASE_LOCAL_DEPS) {
	    struct parsec_vp_s **vps = es->virtual_process->parsec_context->virtual_processes;
	    data_repo_entry_addto_usage_limit(read_B0_repo, arg.output_entry->ht_item.key, arg.output_usage);
	    for (__vp_id = 0; __vp_id < es->virtual_process->parsec_context->nb_vp; __vp_id++) {
		if (NULL == arg.ready_lists[__vp_id])
		    continue;
		if (__vp_id == es->virtual_process->vp_id) {
		    __parsec_schedule(es, arg.ready_lists[__vp_id], 0);
		} else {
		    __parsec_schedule(vps[__vp_id]->execution_streams[0], arg.ready_lists[__vp_id], 0);
		}
		arg.ready_lists[__vp_id] = NULL;
	    }
	}
	if (action_mask & PARSEC_ACTION_RELEASE_LOCAL_REFS) {
	    if (NULL != this_task->data._f_B.data_in) {
		PARSEC_DATA_COPY_RELEASE(this_task->data._f_B.data_in);
	    }
	}
	PARSEC_PINS(es, RELEASE_DEPS_END, (parsec_task_t *) this_task);
    }
    return 0;
}

static int data_lookup_of_dtrsm_LLN_read_B0(parsec_execution_stream_t * es,
					    __parsec_dtrsm_LLN_read_B0_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_assignment_t generic_locals[MAX_PARAM_COUNT];	/* generic task locals */
    int target_device = 0;
    (void) target_device;
    (void) __parsec_tp;
    (void) generic_locals;
    (void) es;
    parsec_data_copy_t *chunk = NULL;
    data_repo_entry_t *entry = NULL;
    const int k = this_task->locals.k.value;
    (void) k;
  /** Lookup the input data, and store them in the context if any */
    this_task->data._f_B.data_out = NULL;	/* By default, if nothing matches */

    if (NULL == (chunk = this_task->data._f_B.data_in)) {	/* flow B */
	entry = NULL;
	chunk = parsec_data_get_copy(data_of_descB(k, 0), target_device);
	PARSEC_OBJ_RETAIN(chunk);
	this_task->data._f_B.data_out = chunk;
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(data_of_descB(k, 0), (parsec_task_t *) this_task,
				       &flow_of_dtrsm_LLN_read_B0_for_B, 1);
#endif
	this_task->data._f_B.data_in = chunk;	/* flow B */
	this_task->data._f_B.data_repo = entry;
    } else {
	this_task->data._f_B.data_out = parsec_data_get_copy(chunk->original, target_device);
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(chunk->original, (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_read_B0_for_B,
				       0);
#endif
    }
  /** Generate profiling information */
#if defined(PARSEC_PROF_TRACE)
    this_task->prof_info.desc = (parsec_data_collection_t *) __parsec_tp->super._g_descB;
    this_task->prof_info.data_id =
	((parsec_data_collection_t *) __parsec_tp->super._g_descB)->data_key((parsec_data_collection_t *) __parsec_tp->
									     super._g_descB, k, 0);
    this_task->prof_info.task_class_id = this_task->task_class->task_class_id;
#endif /* defined(PARSEC_PROF_TRACE) */
    (void) k;
    (void) chunk;
    (void) entry;

    return PARSEC_HOOK_RETURN_DONE;
}

static int datatype_lookup_of_dtrsm_LLN_read_B0(parsec_execution_stream_t * es,
						const __parsec_dtrsm_LLN_read_B0_task_t * this_task,
						uint32_t * flow_mask, parsec_dep_data_description_t * data)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    (void) __parsec_tp;
    (void) es;
    (void) this_task;
    (void) data;
    const int k = this_task->locals.k.value;
    (void) k;
    if ((*flow_mask) & 0x80000000U) {	/* these are the input flows */
	if ((*flow_mask) & 0x1U) {	/* Flow B */
	    if (((*flow_mask) & 0x1U)) {	/* Have unconditional! */
		data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_FULL_ARENA];
		data->layout = data->arena->opaque_dtt;
		data->count = 1;
		data->displ = 0;
		(*flow_mask) &= ~0x1U;
		return PARSEC_HOOK_RETURN_NEXT;
	    }
	}			/* (flow_mask & 0x1U) */
	goto no_mask_match;
    }				/* input flows */
    if ((*flow_mask) & 0x3U) {	/* Flow B */
	if (((*flow_mask) & 0x3U)
	    && ((k == 0) || (k >= 1))) {
	    data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	    data->layout = data->arena->opaque_dtt;
	    data->count = 1;
	    data->displ = 0;
	    (*flow_mask) &= ~0x3U;
	    return PARSEC_HOOK_RETURN_NEXT;
	}
    }				/* (flow_mask & 0x3U) */
  no_mask_match:
    data->arena = NULL;
    data->data = NULL;
    data->layout = PARSEC_DATATYPE_NULL;
    data->count = 0;
    data->displ = 0;
    (*flow_mask) = 0;		/* nothing left */
    (void) k;
    return PARSEC_HOOK_RETURN_DONE;
}

static int hook_of_dtrsm_LLN_read_B0(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_read_B0_task_t * this_task)
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    (void) es;
    (void) __parsec_tp;
    const int k = this_task->locals.k.value;
    (void) k;
    (void) k;

  /** Declare the variables that will hold the data, and all the accounting for each */
    parsec_data_copy_t *_f_B = this_task->data._f_B.data_in;
    void *B = PARSEC_DATA_COPY_GET_PTR(_f_B);
    (void) B;

  /** Update starting simulation date */
#if defined(PARSEC_SIM)
    {
	this_task->sim_exec_date = 0;
	data_repo_entry_t *eB = this_task->data._f_B.data_repo;
	if ((NULL != eB) && (eB->sim_exec_date > this_task->sim_exec_date))
	    this_task->sim_exec_date = eB->sim_exec_date;
	if (this_task->task_class->sim_cost_fct != NULL) {
	    this_task->sim_exec_date += this_task->task_class->sim_cost_fct(this_task);
	}
	if (es->largest_simulation_date < this_task->sim_exec_date)
	    es->largest_simulation_date = this_task->sim_exec_date;
    }
#endif
  /** Transfer the ownership to the CPU */
#if defined(PARSEC_HAVE_CUDA)
    if (NULL != _f_B) {
	parsec_data_transfer_ownership_to_copy(_f_B->original, 0 /* device */ ,
					       PARSEC_FLOW_ACCESS_RW);
    }
#endif /* defined(PARSEC_HAVE_CUDA) */
  /** Cache Awareness Accounting */
#if defined(PARSEC_CACHE_AWARENESS)
    cache_buf_referenced(es->closest_cache, B);
#endif /* PARSEC_CACHE_AWARENESS */


#if !defined(PARSEC_PROF_DRY_BODY)

/*-----                                  read_B0 BODY                                  -----*/

    PARSEC_TASK_PROF_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id],
			   (parsec_task_t *) this_task);
#line 76 "dtrsm_LLN.jdf"
    {
	/* nothing */
    }

#line 2784 "dtrsm_LLN.c"
/*-----                              END OF read_B0 BODY                              -----*/



#endif /*!defined(PARSEC_PROF_DRY_BODY) */

    return PARSEC_HOOK_RETURN_DONE;
}

static int complete_hook_of_dtrsm_LLN_read_B0(parsec_execution_stream_t * es,
					      __parsec_dtrsm_LLN_read_B0_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
#if defined(DISTRIBUTED)
    const int k = this_task->locals.k.value;
    (void) k;
#endif /* defined(DISTRIBUTED) */
    (void) es;
    (void) __parsec_tp;
    if (NULL != this_task->data._f_B.data_out) {
#if defined(PARSEC_DEBUG_NOISIER)
	char tmp[128];
#endif
	this_task->data._f_B.data_out->version++;	/* B */
	PARSEC_DEBUG_VERBOSE(10, parsec_debug_output,
			     "Complete hook of %s: change Data copy %p to version %d at %s:%d",
			     parsec_task_snprintf(tmp, 128, (parsec_task_t *) (this_task)),
			     this_task->data._f_B.data_out, this_task->data._f_B.data_out->version, __FILE__, __LINE__);
    }
    PARSEC_TASK_PROF_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id + 1],
			   (parsec_task_t *) this_task);
#if defined(DISTRIBUTED)
  /** If not working on distributed, there is no risk that data is not in place */
    (void) k;

#endif /* DISTRIBUTED */
#if defined(PARSEC_PROF_GRAPHER)
    parsec_prof_grapher_task((parsec_task_t *) this_task, es->th_id, es->virtual_process->vp_id,
			     __jdf2c_key_fns_read_B0.key_hash(this_task->task_class->
							      make_key((parsec_taskpool_t *) this_task->taskpool,
								       ((parsec_task_t *) this_task)->locals), NULL));
#endif /* defined(PARSEC_PROF_GRAPHER) */
    release_deps_of_dtrsm_LLN_read_B0(es, this_task, PARSEC_ACTION_RELEASE_REMOTE_DEPS | PARSEC_ACTION_RELEASE_LOCAL_DEPS | PARSEC_ACTION_RELEASE_LOCAL_REFS | 0x3,	/* mask of all dep_index */
				      NULL);
    return PARSEC_HOOK_RETURN_DONE;
}

static parsec_hook_return_t release_task_of_dtrsm_LLN_read_B0(parsec_execution_stream_t * es, parsec_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_hash_table_t *ht = (parsec_hash_table_t *) __parsec_tp->super.super.dependencies_array[1];
    parsec_key_t key =
	this_task->task_class->make_key((const parsec_taskpool_t *) __parsec_tp,
					(const parsec_assignment_t *) &this_task->locals);
    parsec_hashable_dependency_t *hash_dep = (parsec_hashable_dependency_t *) parsec_hash_table_remove(ht, key);
    parsec_thread_mempool_free(hash_dep->mempool_owner, hash_dep);
    return parsec_release_task_to_mempool_update_nbtasks(es, this_task);
}

static char *dtrsm_LLN_dtrsm_LLN_read_B0_internal_init_deps_key_functions_key_print(char *buffer, size_t buffer_size,
										    parsec_key_t __parsec_key_,
										    void *user_data)
{
    uint64_t __parsec_key = (uint64_t) (uintptr_t) __parsec_key_;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (__parsec_dtrsm_LLN_internal_taskpool_t *) user_data;
    int k = (__parsec_key) % __parsec_tp->read_B0_k_range;
    __parsec_key = __parsec_key / __parsec_tp->read_B0_k_range;
    snprintf(buffer, buffer_size, "read_B0(%d)", k);
    return buffer;
}

static parsec_key_fn_t dtrsm_LLN_dtrsm_LLN_read_B0_internal_init_deps_key_functions = {
    .key_equal = parsec_hash_table_generic_64bits_key_equal,
    .key_print = dtrsm_LLN_dtrsm_LLN_read_B0_internal_init_deps_key_functions_key_print,
    .key_hash = parsec_hash_table_generic_64bits_key_hash
};

/* Needs: min-max count-tasks iterate */
static int dtrsm_LLN_read_B0_internal_init(parsec_execution_stream_t * es,
					   __parsec_dtrsm_LLN_read_B0_task_t * this_task)
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    int32_t nb_tasks = 0, saved_nb_tasks = 0;
    int32_t __k_min = 0x7fffffff, __k_max = 0;
    int32_t __jdf2c_k_min = 0x7fffffff, __jdf2c_k_max = 0;
    __parsec_dtrsm_LLN_read_B0_parsec_assignment_t assignments;
    int32_t k;
    int32_t __jdf2c_k_start, __jdf2c_k_end, __jdf2c_k_inc;
#if defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
    PARSEC_PROFILING_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id],
			   0, this_task->taskpool->taskpool_id, NULL);
#endif /* defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
    __jdf2c_k_start = 0;
    __jdf2c_k_end = (descB->mt - 1);
    __jdf2c_k_inc = 1;
    __k_min = parsec_imin(__jdf2c_k_start, __jdf2c_k_end);
    __k_max = parsec_imax(__jdf2c_k_start, __jdf2c_k_end);
    __jdf2c_k_min = parsec_imin(__jdf2c_k_min, __k_min);
    __jdf2c_k_max = parsec_imax(__jdf2c_k_max, __k_max);
    for (k = __jdf2c_k_start; k <= __jdf2c_k_end; k += __jdf2c_k_inc) {
	assignments.k.value = k;
	if (!read_B0_pred(k))
	    continue;
	nb_tasks++;
    }				/* Loop on normal range k */
    if (0 != nb_tasks) {
	(void) parsec_atomic_fetch_add_int32(&__parsec_tp->super.super.nb_tasks, nb_tasks);
    }
    saved_nb_tasks = nb_tasks;
    /* Set the range variables for the collision-free hash-computation */
    __parsec_tp->read_B0_k_range = (__jdf2c_k_max - __jdf2c_k_min) + 1;
    do {
	this_task->super.list_next = (parsec_list_item_t *) __parsec_tp->startup_queue;
    } while (!parsec_atomic_cas_ptr
	     (&__parsec_tp->startup_queue, (parsec_list_item_t *) this_task->super.list_next, this_task));
    this_task->status = PARSEC_TASK_STATUS_HOOK;

    PARSEC_AYU_REGISTER_TASK(&dtrsm_LLN_read_B0);
    __parsec_tp->super.super.dependencies_array[1] = PARSEC_OBJ_NEW(parsec_hash_table_t);
    parsec_hash_table_init(__parsec_tp->super.super.dependencies_array[1],
			   offsetof(parsec_hashable_dependency_t, ht_item), 10,
			   dtrsm_LLN_dtrsm_LLN_read_B0_internal_init_deps_key_functions, this_task->taskpool);
    __parsec_tp->repositories[1] =
	data_repo_create_nothreadsafe(nb_tasks, __jdf2c_key_fns_read_B0, (parsec_taskpool_t *) __parsec_tp, 1);
    (void) saved_nb_tasks;
    (void) __k_min;
    (void) __k_max;
    (void) __jdf2c_k_start;
    (void) __jdf2c_k_end;
    (void) __jdf2c_k_inc;
    (void) assignments;
    (void) __parsec_tp;
    (void) es;
    if (1 == parsec_atomic_fetch_dec_int32(&__parsec_tp->sync_point)) {
	/* Last initialization task complete. Update the number of tasks. */
	nb_tasks = parsec_atomic_fetch_dec_int32(&__parsec_tp->super.super.nb_tasks);
	parsec_mfence();	/* write memory barrier to guarantee that the scheduler gets the correct number of tasks */
	parsec_taskpool_enable((parsec_taskpool_t *) __parsec_tp, &__parsec_tp->startup_queue,
			       (parsec_task_t *) this_task, es, (1 <= nb_tasks));
#if defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
	PARSEC_PROFILING_TRACE(es->es_profile,
			       this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id + 1],
			       0, this_task->taskpool->taskpool_id, NULL);
#endif /* defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
	if (1 >= nb_tasks) {
	    /* if no tasks will be generated let's prevent the runtime from calling the hook and instead go directly to complete the task */
	    this_task->status = PARSEC_TASK_STATUS_COMPLETE;
	}
	return PARSEC_HOOK_RETURN_DONE;
    }
    return PARSEC_HOOK_RETURN_ASYNC;
}

static int __jdf2c_startup_read_B0(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_read_B0_task_t * this_task)
{
    __parsec_dtrsm_LLN_read_B0_task_t *new_task;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_context_t *context = __parsec_tp->super.super.context;
    int vpid = 0, nb_tasks = 0;
    size_t total_nb_tasks = 0;
    parsec_list_item_t *pready_ring[context->nb_vp];
    int restore_context = 0;
    int k = this_task->locals.k.value;	/* retrieve value saved during the last iteration */
    for (int _i = 0; _i < context->nb_vp; pready_ring[_i++] = NULL);
    if (0 != this_task->locals.reserved[0].value) {
	this_task->locals.reserved[0].value = 1;	/* reset the submission process */
	restore_context = 1;
	goto restore_context_0;
    }
    this_task->locals.reserved[0].value = 1;	/* a sane default value */
    for (this_task->locals.k.value = k = 0;
	 this_task->locals.k.value <= (descB->mt - 1); this_task->locals.k.value += 1, k = this_task->locals.k.value) {
	if (!read_B0_pred(k))
	    continue;
	__parsec_dtrsm_LLN_read_B0_parsec_assignment_t __jdf2c__tmp_locals =
	    *(__parsec_dtrsm_LLN_read_B0_parsec_assignment_t *) & this_task->locals;
	(void) __jdf2c__tmp_locals;
	/* Flow for B is always a memory reference */
	if (NULL != ((parsec_data_collection_t *) __parsec_tp->super._g_descB)->vpid_of) {
	    vpid =
		((parsec_data_collection_t *) __parsec_tp->super._g_descB)->
		vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descB, k, 0);
	    assert(context->nb_vp >= vpid);
	}
	new_task =
	    (__parsec_dtrsm_LLN_read_B0_task_t *) parsec_thread_mempool_allocate(context->virtual_processes[vpid]->
										 execution_streams[0]->context_mempool);
	new_task->status = PARSEC_TASK_STATUS_NONE;
	/* Copy only the valid elements from this_task to new_task one */
	new_task->taskpool = this_task->taskpool;
	new_task->task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_read_B0.task_class_id];
	new_task->chore_id = 0;
	new_task->locals.k.value = this_task->locals.k.value;
	PARSEC_LIST_ITEM_SINGLETON(new_task);
	new_task->priority = __parsec_tp->super.super.priority;
	new_task->data._f_B.data_repo = NULL;
	new_task->data._f_B.data_in = NULL;
	new_task->data._f_B.data_out = NULL;
#if defined(PARSEC_DEBUG_NOISIER)
	{
	    char tmp[128];
	    PARSEC_DEBUG_VERBOSE(10, parsec_debug_output, "Add startup task %s to vpid %d",
				 parsec_task_snprintf(tmp, 128, (parsec_task_t *) new_task), vpid);
	}
#endif
	parsec_dependencies_mark_task_as_startup((parsec_task_t *) new_task, es);
	pready_ring[vpid] = parsec_list_item_ring_push_sorted(pready_ring[vpid],
							      (parsec_list_item_t *) new_task,
							      parsec_execution_context_priority_comparator);
	nb_tasks++;
      restore_context_0:	/* we jump here just so that we have code after the label */
	restore_context = 0;
	(void) restore_context;
	if (nb_tasks > this_task->locals.reserved[0].value) {
	    if ((size_t) this_task->locals.reserved[0].value < parsec_task_startup_iter)
		this_task->locals.reserved[0].value <<= 1;
	    for (int _i = 0; _i < context->nb_vp; _i++) {
		if (NULL == pready_ring[_i])
		    continue;
		__parsec_schedule(context->virtual_processes[_i]->execution_streams[0],
				  (parsec_task_t *) pready_ring[_i], 0);
		pready_ring[_i] = NULL;
	    }
	    total_nb_tasks += nb_tasks;
	    nb_tasks = 0;
	    if (total_nb_tasks > parsec_task_startup_chunk) {	/* stop here and request to be rescheduled */
		return PARSEC_HOOK_RETURN_AGAIN;
	    }
	}
    }				/* Loop on normal range k */
    (void) vpid;
    if (0 != nb_tasks) {
	for (int _i = 0; _i < context->nb_vp; _i++) {
	    if (NULL == pready_ring[_i])
		continue;
	    __parsec_schedule(context->virtual_processes[_i]->execution_streams[0],
			      (parsec_task_t *) pready_ring[_i], 0);
	    pready_ring[_i] = NULL;
	}
	nb_tasks = 0;
    }
    return PARSEC_HOOK_RETURN_DONE;
}

static const __parsec_chore_t __dtrsm_LLN_read_B0_chores[] = {
    {.type = PARSEC_DEV_CPU,
     .evaluate = NULL,
     .hook = (parsec_hook_t *) hook_of_dtrsm_LLN_read_B0},
    {.type = PARSEC_DEV_NONE,
     .evaluate = NULL,
     .hook = (parsec_hook_t *) NULL},	/* End marker */
};

static const parsec_task_class_t dtrsm_LLN_read_B0 = {
    .name = "read_B0",
    .task_class_id = 1,
    .nb_flows = 1,
    .nb_parameters = 1,
    .nb_locals = 1,
    .params = {&symb_dtrsm_LLN_read_B0_k, NULL},
    .locals = {&symb_dtrsm_LLN_read_B0_k, NULL},
    .data_affinity = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_read_B0,
    .initial_data = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_read_B0,
    .final_data = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_read_B0,
    .priority = NULL,
    .properties = properties_of_dtrsm_LLN_read_B0,
#if MAX_PARAM_COUNT < 1		/* number of read flows of read_B0 */
#error Too many read flows for task read_B0
#endif /* MAX_PARAM_COUNT */
#if MAX_PARAM_COUNT < 1		/* number of write flows of read_B0 */
#error Too many write flows for task read_B0
#endif /* MAX_PARAM_COUNT */
    .in = {&flow_of_dtrsm_LLN_read_B0_for_B, NULL},
    .out = {&flow_of_dtrsm_LLN_read_B0_for_B, NULL},
    .flags = 0x0 | PARSEC_HAS_IN_IN_DEPENDENCIES | PARSEC_USE_DEPS_MASK,
    .dependencies_goal = 0x1,
    .make_key = __jdf2c_make_key_read_B0,
    .key_functions = &__jdf2c_key_fns_read_B0,
    .fini = (parsec_hook_t *) NULL,
    .incarnations = __dtrsm_LLN_read_B0_chores,
    .find_deps = parsec_hash_find_deps,
    .iterate_successors = (parsec_traverse_function_t *) iterate_successors_of_dtrsm_LLN_read_B0,
    .iterate_predecessors = (parsec_traverse_function_t *) NULL,
    .release_deps = (parsec_release_deps_t *) release_deps_of_dtrsm_LLN_read_B0,
    .prepare_input = (parsec_hook_t *) data_lookup_of_dtrsm_LLN_read_B0,
    .prepare_output = (parsec_hook_t *) NULL,
    .get_datatype = (parsec_datatype_lookup_t *) datatype_lookup_of_dtrsm_LLN_read_B0,
    .complete_execution = (parsec_hook_t *) complete_hook_of_dtrsm_LLN_read_B0,
    .release_task = &release_task_of_dtrsm_LLN_read_B0,
#if defined(PARSEC_SIM)
    .sim_cost_fct = (parsec_sim_cost_fct_t *) NULL,
#endif
};


/******                                    dtrsm                                      ******/

static inline int32_t minexpr_of_symb_dtrsm_LLN_dtrsm_k_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							    const __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t * locals)
{
    (void) __parsec_tp;
    (void) locals;
    return 0;
}

static const parsec_expr_t minexpr_of_symb_dtrsm_LLN_dtrsm_k = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) minexpr_of_symb_dtrsm_LLN_dtrsm_k_fct}
		      }
};

static inline int maxexpr_of_symb_dtrsm_LLN_dtrsm_k_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							const __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t * locals)
{
    const int k = locals->k.value;
    (void) k;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (descB->mt - 1);
}

static const parsec_expr_t maxexpr_of_symb_dtrsm_LLN_dtrsm_k = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) maxexpr_of_symb_dtrsm_LLN_dtrsm_k_fct}
		      }
};
static const parsec_symbol_t symb_dtrsm_LLN_dtrsm_k = {.name = "k",.context_index = 0,.min =
	&minexpr_of_symb_dtrsm_LLN_dtrsm_k,.max = &maxexpr_of_symb_dtrsm_LLN_dtrsm_k,.cst_inc = 1,.expr_inc =
	NULL,.flags = 0x0 };

static inline int32_t expr_of_symb_dtrsm_LLN_dtrsm_n_fct(const __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
							 const __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t * locals)
{
    (void) __parsec_tp;
    (void) locals;
    return 0;
}

static const parsec_expr_t expr_of_symb_dtrsm_LLN_dtrsm_n = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) expr_of_symb_dtrsm_LLN_dtrsm_n_fct}
		      }
};
static const parsec_symbol_t symb_dtrsm_LLN_dtrsm_n = {.name = "n",.context_index = 1,.min =
	&expr_of_symb_dtrsm_LLN_dtrsm_n,.max = &expr_of_symb_dtrsm_LLN_dtrsm_n,.cst_inc = 0,.expr_inc = NULL,.flags =
	PARSEC_SYMBOL_IS_STANDALONE };

static inline int affinity_of_dtrsm_LLN_dtrsm(__parsec_dtrsm_LLN_dtrsm_task_t * this_task, parsec_data_ref_t * ref)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    const int k = this_task->locals.k.value;
    (void) k;
    const int n = this_task->locals.n.value;
    (void) n;

    /* Silent Warnings: should look into predicate to know what variables are usefull */
    (void) k;
    (void) n;
    ref->dc = (parsec_data_collection_t *) __parsec_tp->super._g_descA;
    /* Compute data key */
    ref->key = ref->dc->data_key(ref->dc, k, k);
    return 1;
}

static inline int32_t property_2_flops_of_dtrsm_LLN_dtrsm_as_expr_fct(const __parsec_dtrsm_LLN_internal_taskpool_t *
								      __parsec_tp,
								      const __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t
								      * locals)
{
    (void) __parsec_tp;
    (void) locals;
    return dtrsm_LLN_dtrsm_inline_c_expr2_line_26(__parsec_tp, locals);
}

static const parsec_expr_t property_2_flops_of_dtrsm_LLN_dtrsm_as_expr = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t) property_2_flops_of_dtrsm_LLN_dtrsm_as_expr_fct}
		      }
};

static const parsec_property_t properties_of_dtrsm_LLN_dtrsm[2] = {
    {.name = "flops",.expr = &property_2_flops_of_dtrsm_LLN_dtrsm_as_expr},
    {.name = NULL,.expr = NULL}
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep1_atline_35_fct(const
										    __parsec_dtrsm_LLN_internal_taskpool_t
										    * __parsec_tp,
										    const
										    __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t
										    * locals)
{
    const int k = locals->k.value;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (k >= 1);
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep1_atline_35 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep1_atline_35_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dtrsm_for_B_dep1_atline_35 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep1_atline_35,	/* (k >= 1) */
    .ctl_gather_nb = NULL,
    .task_class_id = 3,		/* dtrsm_LLN_dgemm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dgemm_for_E,
    .dep_index = 1,
    .dep_datatype_index = 1,
    .belongs_to = &flow_of_dtrsm_LLN_dtrsm_for_B,
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep2_atline_36_fct(const
										    __parsec_dtrsm_LLN_internal_taskpool_t
										    * __parsec_tp,
										    const
										    __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t
										    * locals)
{
    const int k = locals->k.value;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (0 == k);
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep2_atline_36 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep2_atline_36_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dtrsm_for_B_dep2_atline_36 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep2_atline_36,	/* (0 == k) */
    .ctl_gather_nb = NULL,
    .task_class_id = 1,		/* dtrsm_LLN_read_B0 */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_read_B0_for_B,
    .dep_index = 2,
    .dep_datatype_index = 1,
    .belongs_to = &flow_of_dtrsm_LLN_dtrsm_for_B,
};

static const parsec_dep_t flow_of_dtrsm_LLN_dtrsm_for_B_dep3_atline_37 = {
    .cond = NULL,		/*  */
    .ctl_gather_nb = NULL,
    .task_class_id = 2,		/* dtrsm_LLN_write_B0 */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_write_B0_for_B,
    .dep_index = 0,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_dtrsm_for_B,
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep4_atline_38_fct(const
										    __parsec_dtrsm_LLN_internal_taskpool_t
										    * __parsec_tp,
										    const
										    __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t
										    * locals)
{
    const int k = locals->k.value;
    (void) k;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return (descB->mt >= (k + 2));
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep4_atline_38 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep4_atline_38_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dtrsm_for_B_dep4_atline_38 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_B_dep4_atline_38,	/* (descB->mt >= (k + 2)) */
    .ctl_gather_nb = NULL,
    .task_class_id = 3,		/* dtrsm_LLN_dgemm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dgemm_for_D,
    .dep_index = 1,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_dtrsm_for_B,
};

#if MAX_DEP_IN_COUNT < 2	/* number of input dependencies */
#error Too many input dependencies (supports up to MAX_DEP_IN_COUNT [=10] but found 2). Fix the code or recompile PaRSEC with a larger MAX_DEP_IN_COUNT.
#endif
#if MAX_DEP_OUT_COUNT < 2	/* number of output dependencies */
#error Too many output dependencies (supports up to MAX_DEP_OUT_COUNT [=10] but found 2). Fix the code or recompile PaRSEC with a larger MAX_DEP_OUT_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_dtrsm_for_B = {
    .name = "B",
    .sym_type = PARSEC_SYM_INOUT,
    .flow_flags = PARSEC_FLOW_ACCESS_RW,
    .flow_index = 0,
    .flow_datatype_mask = 0x1,
    .dep_in = {&flow_of_dtrsm_LLN_dtrsm_for_B_dep1_atline_35,
	       &flow_of_dtrsm_LLN_dtrsm_for_B_dep2_atline_36},
    .dep_out = {&flow_of_dtrsm_LLN_dtrsm_for_B_dep3_atline_37,
		&flow_of_dtrsm_LLN_dtrsm_for_B_dep4_atline_38}
};

static parsec_data_t *flow_of_dtrsm_LLN_dtrsm_for_A_dep1_atline_33_direct_access(const
										 __parsec_dtrsm_LLN_internal_taskpool_t
										 * __parsec_tp,
										 const
										 __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t
										 * assignments)
{
    const int k = assignments->k.value;
    (void) k;
    const int n = assignments->n.value;
    (void) n;

    /* Silence Warnings: should look into parameters to know what variables are useful */
    (void) k;
    (void) n;
    if (__parsec_tp->super.super.context->my_rank == (int32_t) rank_of_descA(k, k))
	return data_of_descA(k, k);
    return NULL;
}

static const parsec_dep_t flow_of_dtrsm_LLN_dtrsm_for_A_dep1_atline_33 = {
    .cond = NULL,		/*  */
    .ctl_gather_nb = NULL,
    .task_class_id = PARSEC_LOCAL_DATA_TASK_CLASS_ID,	/* dtrsm_LLN_descA */
    .direct_data = (parsec_data_lookup_func_t) & flow_of_dtrsm_LLN_dtrsm_for_A_dep1_atline_33_direct_access,
    .dep_index = 0,
    .dep_datatype_index = 0,
    .belongs_to = &flow_of_dtrsm_LLN_dtrsm_for_A,
};

#if MAX_DEP_IN_COUNT < 1	/* number of input dependencies */
#error Too many input dependencies (supports up to MAX_DEP_IN_COUNT [=10] but found 1). Fix the code or recompile PaRSEC with a larger MAX_DEP_IN_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_dtrsm_for_A = {
    .name = "A",
    .sym_type = PARSEC_SYM_IN,
    .flow_flags = PARSEC_FLOW_ACCESS_READ | PARSEC_FLOW_HAS_IN_DEPS,
    .flow_index = 1,
    .flow_datatype_mask = 0x0,
    .dep_in = {&flow_of_dtrsm_LLN_dtrsm_for_A_dep1_atline_33},
    .dep_out = {NULL}
};

static inline int expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_ctl_dep1_atline_39_fct(const
										      __parsec_dtrsm_LLN_internal_taskpool_t
										      * __parsec_tp,
										      const
										      __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t
										      * locals)
{
    const int k = locals->k.value;
    const int n = locals->n.value;
    (void) n;

    (void) k;
    (void) n;
    (void) __parsec_tp;
    (void) locals;
    return ((k > 0) && (k <= 500));
}

static const parsec_expr_t expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_ctl_dep1_atline_39 = {
    .op = PARSEC_EXPR_OP_INLINE,
    .u_expr.v_func = {.type = PARSEC_RETURN_TYPE_INT32,	/* PARSEC_RETURN_TYPE_INT32 */
		      .func = {.inline_func_int32 =
			       (parsec_expr_op_int32_inline_func_t)
			       expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_ctl_dep1_atline_39_fct}
		      }
};

static const parsec_dep_t flow_of_dtrsm_LLN_dtrsm_for_ctl_dep1_atline_39 = {
    .cond = &expr_of_cond_for_flow_of_dtrsm_LLN_dtrsm_for_ctl_dep1_atline_39,	/* ((k > 0) && (k <= 500)) */
    .ctl_gather_nb = NULL,
    .task_class_id = 3,		/* dtrsm_LLN_dgemm */
    .direct_data = (parsec_data_lookup_func_t) NULL,
    .flow = &flow_of_dtrsm_LLN_dgemm_for_ctl,
    .dep_index = 2,
    .dep_datatype_index = 2,
    .belongs_to = &flow_of_dtrsm_LLN_dtrsm_for_ctl,
};

#if MAX_DEP_OUT_COUNT < 1	/* number of output dependencies */
#error Too many output dependencies (supports up to MAX_DEP_OUT_COUNT [=10] but found 1). Fix the code or recompile PaRSEC with a larger MAX_DEP_OUT_COUNT.
#endif

static const parsec_flow_t flow_of_dtrsm_LLN_dtrsm_for_ctl = {
    .name = "ctl",
    .sym_type = PARSEC_SYM_OUT,
    .flow_flags = PARSEC_FLOW_ACCESS_NONE,
    .flow_index = 2,
    .flow_datatype_mask = 0x4,
    .dep_in = {NULL},
    .dep_out = {&flow_of_dtrsm_LLN_dtrsm_for_ctl_dep1_atline_39}
};

static void
iterate_successors_of_dtrsm_LLN_dtrsm(parsec_execution_stream_t * es, const __parsec_dtrsm_LLN_dtrsm_task_t * this_task,
				      uint32_t action_mask, parsec_ontask_function_t * ontask, void *ontask_arg)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_task_t nc;		/* generic placeholder for locals */
    parsec_dep_data_description_t data;
    __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t __jdf2c__tmp_locals = *(__parsec_dtrsm_LLN_dtrsm_parsec_assignment_t *) & this_task->locals;	/* copy of this_task locals in R/W mode to manage local definitions */
    int vpid_dst = -1, rank_src = 0, rank_dst = 0;
    const int k = __jdf2c__tmp_locals.k.value;
    (void) k;
    const int n = __jdf2c__tmp_locals.n.value;
    (void) n;
    (void) rank_src;
    (void) rank_dst;
    (void) __parsec_tp;
    (void) vpid_dst;
    (void) k;
    (void) n;
    nc.taskpool = this_task->taskpool;
    nc.priority = this_task->priority;
    nc.chore_id = 0;
#if defined(DISTRIBUTED)
    rank_src = rank_of_descA(k, k);
#endif
    if (action_mask & 0x3) {	/* Flow of data B */
	data.data = this_task->data._f_B.data_out;
	data.arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	data.layout = data.arena->opaque_dtt;
	data.count = 1;
	data.displ = 0;
	if (action_mask & 0x1) {
	    __parsec_dtrsm_LLN_write_B0_task_t *ncc = (__parsec_dtrsm_LLN_write_B0_task_t *) & nc;
	    nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_write_B0.task_class_id];
	    const int write_B0_k = k;
	    if ((write_B0_k >= (0)) && (write_B0_k <= ((descB->mt - 1)))) {
		assert(&nc.locals[0].value == &ncc->locals.k.value);
		ncc->locals.k.value = write_B0_k;
#if defined(DISTRIBUTED)
		rank_dst = rank_of_descB(ncc->locals.k.value, 0);
		if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
		    vpid_dst =
			((parsec_data_collection_t *) __parsec_tp->super._g_descB)->
			vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descB, ncc->locals.k.value, 0);
		nc.priority = __parsec_tp->super.super.priority;
		RELEASE_DEP_OUTPUT(es, "B", this_task, "B", &nc, rank_src, rank_dst, &data);
		if (PARSEC_ITERATE_STOP ==
		    ontask(es, &nc, (const parsec_task_t *) this_task, &flow_of_dtrsm_LLN_dtrsm_for_B_dep3_atline_37,
			   &data, rank_src, rank_dst, vpid_dst, ontask_arg))
		    return;
	    }
	}
	if (action_mask & 0x2) {
	    if ((descB->mt >= (k + 2))) {
		__parsec_dtrsm_LLN_dgemm_task_t *ncc = (__parsec_dtrsm_LLN_dgemm_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dgemm.task_class_id];
		const int dgemm_k = k;
		if ((dgemm_k >= (0)) && (dgemm_k <= ((descB->mt - 2)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = dgemm_k;
		    int dgemm_m;
		    for (dgemm_m = (k + 1); dgemm_m <= (descB->mt - 1); dgemm_m += 1) {
			if ((dgemm_m >= ((ncc->locals.k.value + 1))) && (dgemm_m <= ((descB->mt - 1)))) {
			    assert(&nc.locals[1].value == &ncc->locals.m.value);
			    ncc->locals.m.value = dgemm_m;
			    const int dgemm_n = n;
			    if ((dgemm_n == (0))) {
				assert(&nc.locals[2].value == &ncc->locals.n.value);
				ncc->locals.n.value = dgemm_n;
#if defined(DISTRIBUTED)
				rank_dst = rank_of_descA(ncc->locals.m.value, ncc->locals.k.value);
				if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
				    vpid_dst =
					((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
					vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA,
						ncc->locals.m.value, ncc->locals.k.value);
				nc.priority = __parsec_tp->super.super.priority;
				RELEASE_DEP_OUTPUT(es, "B", this_task, "D", &nc, rank_src, rank_dst, &data);
				if (PARSEC_ITERATE_STOP ==
				    ontask(es, &nc, (const parsec_task_t *) this_task,
					   &flow_of_dtrsm_LLN_dtrsm_for_B_dep4_atline_38, &data, rank_src, rank_dst,
					   vpid_dst, ontask_arg))
				    return;
			    }
			}
		    }
		}
	    }
	}
    }
    /* Flow of data A has only IN dependencies */
    if (action_mask & 0x4) {	/* Flow of data ctl */
	data.data = this_task->data._f_ctl.data_out;
	data.arena = NULL;
	data.layout = PARSEC_DATATYPE_NULL;
	data.count = /* Control: always empty */ 0;
	data.displ = 0;
	if (((k > 0) && (k <= 500))) {
	    __parsec_dtrsm_LLN_dgemm_task_t *ncc = (__parsec_dtrsm_LLN_dgemm_task_t *) & nc;
	    nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dgemm.task_class_id];
	    const int dgemm_k = (k - 1);
	    if ((dgemm_k >= (0)) && (dgemm_k <= ((descB->mt - 2)))) {
		assert(&nc.locals[0].value == &ncc->locals.k.value);
		ncc->locals.k.value = dgemm_k;
		int dgemm_m;
		for (dgemm_m = (k + 32); dgemm_m <= (descB->mt - 1); dgemm_m += 1) {
		    if ((dgemm_m >= ((ncc->locals.k.value + 1))) && (dgemm_m <= ((descB->mt - 1)))) {
			assert(&nc.locals[1].value == &ncc->locals.m.value);
			ncc->locals.m.value = dgemm_m;
			const int dgemm_n = n;
			if ((dgemm_n == (0))) {
			    assert(&nc.locals[2].value == &ncc->locals.n.value);
			    ncc->locals.n.value = dgemm_n;
#if defined(DISTRIBUTED)
			    rank_dst = rank_of_descA(ncc->locals.m.value, ncc->locals.k.value);
			    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
				vpid_dst =
				    ((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
				    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA,
					    ncc->locals.m.value, ncc->locals.k.value);
			    nc.priority = __parsec_tp->super.super.priority;
			    RELEASE_DEP_OUTPUT(es, "ctl", this_task, "ctl", &nc, rank_src, rank_dst, &data);
			    if (PARSEC_ITERATE_STOP ==
				ontask(es, &nc, (const parsec_task_t *) this_task,
				       &flow_of_dtrsm_LLN_dtrsm_for_ctl_dep1_atline_39, &data, rank_src, rank_dst,
				       vpid_dst, ontask_arg))
				return;
			}
		    }
		}
	    }
	}
    }
    (void) data;
    (void) nc;
    (void) es;
    (void) ontask;
    (void) ontask_arg;
    (void) rank_dst;
    (void) action_mask;
}

static void
iterate_predecessors_of_dtrsm_LLN_dtrsm(parsec_execution_stream_t * es,
					const __parsec_dtrsm_LLN_dtrsm_task_t * this_task, uint32_t action_mask,
					parsec_ontask_function_t * ontask, void *ontask_arg)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_task_t nc;		/* generic placeholder for locals */
    parsec_dep_data_description_t data;
    __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t __jdf2c__tmp_locals = *(__parsec_dtrsm_LLN_dtrsm_parsec_assignment_t *) & this_task->locals;	/* copy of this_task locals in R/W mode to manage local definitions */
    int vpid_dst = -1, rank_src = 0, rank_dst = 0;
    const int k = __jdf2c__tmp_locals.k.value;
    (void) k;
    const int n = __jdf2c__tmp_locals.n.value;
    (void) n;
    (void) rank_src;
    (void) rank_dst;
    (void) __parsec_tp;
    (void) vpid_dst;
    (void) k;
    (void) n;
    nc.taskpool = this_task->taskpool;
    nc.priority = this_task->priority;
    nc.chore_id = 0;
#if defined(DISTRIBUTED)
    rank_src = rank_of_descA(k, k);
#endif
    if (action_mask & 0x6) {	/* Flow of data B */
	data.data = this_task->data._f_B.data_out;
	data.arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	data.layout = data.arena->opaque_dtt;
	data.count = 1;
	data.displ = 0;
	if (action_mask & 0x2) {
	    if ((k >= 1)) {
		__parsec_dtrsm_LLN_dgemm_task_t *ncc = (__parsec_dtrsm_LLN_dgemm_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_dgemm.task_class_id];
		const int dgemm_k = (k - 1);
		if ((dgemm_k >= (0)) && (dgemm_k <= ((descB->mt - 2)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = dgemm_k;
		    const int dgemm_m = k;
		    if ((dgemm_m >= ((ncc->locals.k.value + 1))) && (dgemm_m <= ((descB->mt - 1)))) {
			assert(&nc.locals[1].value == &ncc->locals.m.value);
			ncc->locals.m.value = dgemm_m;
			const int dgemm_n = n;
			if ((dgemm_n == (0))) {
			    assert(&nc.locals[2].value == &ncc->locals.n.value);
			    ncc->locals.n.value = dgemm_n;
#if defined(DISTRIBUTED)
			    rank_dst = rank_of_descA(ncc->locals.m.value, ncc->locals.k.value);
			    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
				vpid_dst =
				    ((parsec_data_collection_t *) __parsec_tp->super._g_descA)->
				    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descA,
					    ncc->locals.m.value, ncc->locals.k.value);
			    nc.priority = __parsec_tp->super.super.priority;
			    RELEASE_DEP_OUTPUT(es, "B", this_task, "E", &nc, rank_src, rank_dst, &data);
			    if (PARSEC_ITERATE_STOP ==
				ontask(es, &nc, (const parsec_task_t *) this_task,
				       &flow_of_dtrsm_LLN_dtrsm_for_B_dep1_atline_35, &data, rank_src, rank_dst,
				       vpid_dst, ontask_arg))
				return;
			}
		    }
		}
	    }
	}
	if (action_mask & 0x4) {
	    if ((0 == k)) {
		__parsec_dtrsm_LLN_read_B0_task_t *ncc = (__parsec_dtrsm_LLN_read_B0_task_t *) & nc;
		nc.task_class = __parsec_tp->super.super.task_classes_array[dtrsm_LLN_read_B0.task_class_id];
		const int read_B0_k = k;
		if ((read_B0_k >= (0)) && (read_B0_k <= ((descB->mt - 1)))) {
		    assert(&nc.locals[0].value == &ncc->locals.k.value);
		    ncc->locals.k.value = read_B0_k;
#if defined(DISTRIBUTED)
		    rank_dst = rank_of_descB(ncc->locals.k.value, 0);
		    if ((NULL != es) && (rank_dst == es->virtual_process->parsec_context->my_rank))
#endif /* DISTRIBUTED */
			vpid_dst =
			    ((parsec_data_collection_t *) __parsec_tp->super._g_descB)->
			    vpid_of((parsec_data_collection_t *) __parsec_tp->super._g_descB, ncc->locals.k.value, 0);
		    nc.priority = __parsec_tp->super.super.priority;
		    RELEASE_DEP_OUTPUT(es, "B", this_task, "B", &nc, rank_src, rank_dst, &data);
		    if (PARSEC_ITERATE_STOP ==
			ontask(es, &nc, (const parsec_task_t *) this_task,
			       &flow_of_dtrsm_LLN_dtrsm_for_B_dep2_atline_36, &data, rank_src, rank_dst, vpid_dst,
			       ontask_arg))
			return;
		}
	    }
	}
    }
    /* Flow of data A has only OUTPUT dependencies to Memory */
    /* Flow of data ctl has only IN dependencies */
    (void) data;
    (void) nc;
    (void) es;
    (void) ontask;
    (void) ontask_arg;
    (void) rank_dst;
    (void) action_mask;
}

static int release_deps_of_dtrsm_LLN_dtrsm(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dtrsm_task_t * this_task,
					   uint32_t action_mask, parsec_remote_deps_t * deps)
{
    PARSEC_PINS(es, RELEASE_DEPS_BEGIN, (parsec_task_t *) this_task); {
	const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	    (const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
	parsec_release_dep_fct_arg_t arg;
	int __vp_id;
	arg.action_mask = action_mask;
	arg.output_usage = 0;
	arg.output_entry = NULL;
#if defined(DISTRIBUTED)
	arg.remote_deps = deps;
#endif /* defined(DISTRIBUTED) */
	assert(NULL != es);
	arg.ready_lists = alloca(sizeof(parsec_task_t *) * es->virtual_process->parsec_context->nb_vp);
	for (__vp_id = 0; __vp_id < es->virtual_process->parsec_context->nb_vp; arg.ready_lists[__vp_id++] = NULL);
	(void) __parsec_tp;
	(void) deps;
	if (action_mask & (PARSEC_ACTION_RELEASE_LOCAL_DEPS | PARSEC_ACTION_GET_REPO_ENTRY)) {
	    arg.output_entry =
		data_repo_lookup_entry_and_create(es, dtrsm_repo,
						  __jdf2c_make_key_dtrsm((const parsec_taskpool_t *) __parsec_tp,
									 (const parsec_assignment_t *) &this_task->
									 locals));
	    arg.output_entry->generator = (void *) this_task;	/* for AYU */
#if defined(PARSEC_SIM)
	    assert(arg.output_entry->sim_exec_date == 0);
	    arg.output_entry->sim_exec_date = this_task->sim_exec_date;
#endif
	}
	iterate_successors_of_dtrsm_LLN_dtrsm(es, this_task, action_mask, parsec_release_dep_fct, &arg);

#if defined(DISTRIBUTED)
	if ((action_mask & PARSEC_ACTION_SEND_REMOTE_DEPS) && (NULL != arg.remote_deps)) {
	    parsec_remote_dep_activate(es, (parsec_task_t *) this_task, arg.remote_deps,
				       arg.remote_deps->outgoing_mask);
	}
#endif

	if (action_mask & PARSEC_ACTION_RELEASE_LOCAL_DEPS) {
	    struct parsec_vp_s **vps = es->virtual_process->parsec_context->virtual_processes;
	    data_repo_entry_addto_usage_limit(dtrsm_repo, arg.output_entry->ht_item.key, arg.output_usage);
	    for (__vp_id = 0; __vp_id < es->virtual_process->parsec_context->nb_vp; __vp_id++) {
		if (NULL == arg.ready_lists[__vp_id])
		    continue;
		if (__vp_id == es->virtual_process->vp_id) {
		    __parsec_schedule(es, arg.ready_lists[__vp_id], 0);
		} else {
		    __parsec_schedule(vps[__vp_id]->execution_streams[0], arg.ready_lists[__vp_id], 0);
		}
		arg.ready_lists[__vp_id] = NULL;
	    }
	}
	if (action_mask & PARSEC_ACTION_RELEASE_LOCAL_REFS) {
	    const int k = this_task->locals.k.value;
	    (void) k;
	    const int n = this_task->locals.n.value;
	    (void) n;

	    (void) k;
	    (void) n;

	    if ((k >= 1)) {
		data_repo_entry_used_once(es, dgemm_repo, this_task->data._f_B.data_repo->ht_item.key);
	    } else if ((0 == k)) {
		data_repo_entry_used_once(es, read_B0_repo, this_task->data._f_B.data_repo->ht_item.key);
	    }
	    if (NULL != this_task->data._f_B.data_in) {
		PARSEC_DATA_COPY_RELEASE(this_task->data._f_B.data_in);
	    }
	    if (NULL != this_task->data._f_A.data_in) {
		PARSEC_DATA_COPY_RELEASE(this_task->data._f_A.data_in);
	    }
	}
	PARSEC_PINS(es, RELEASE_DEPS_END, (parsec_task_t *) this_task);
    }
    return 0;
}

static int data_lookup_of_dtrsm_LLN_dtrsm(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dtrsm_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_assignment_t generic_locals[MAX_PARAM_COUNT];	/* generic task locals */
    int target_device = 0;
    (void) target_device;
    (void) __parsec_tp;
    (void) generic_locals;
    (void) es;
    parsec_data_copy_t *chunk = NULL;
    data_repo_entry_t *entry = NULL;
    const int k = this_task->locals.k.value;
    (void) k;
    const int n = this_task->locals.n.value;
    (void) n;
  /** Lookup the input data, and store them in the context if any */
    this_task->data._f_B.data_out = NULL;	/* By default, if nothing matches */

    if (NULL == (chunk = this_task->data._f_B.data_in)) {	/* flow B */
	entry = NULL;
	if ((k >= 1)) {
	    __parsec_dtrsm_LLN_dgemm_parsec_assignment_t *target_locals =
		(__parsec_dtrsm_LLN_dgemm_parsec_assignment_t *) & generic_locals;
	    const int dgemmk = target_locals->k.value = (k - 1);
	    (void) dgemmk;
	    const int dgemmm = target_locals->m.value = k;
	    (void) dgemmm;
	    const int dgemmn = target_locals->n.value = n;
	    (void) dgemmn;
	    entry =
		data_repo_lookup_entry(dgemm_repo,
				       __jdf2c_make_key_dgemm((const parsec_taskpool_t *) __parsec_tp,
							      (const parsec_assignment_t *) target_locals));
	    chunk = entry->data[0];	/* B:dtrsm <- E:dgemm */
	    ACQUIRE_FLOW(this_task, "B", &dtrsm_LLN_dgemm, "E", target_locals, chunk);
	    this_task->data._f_B.data_out = chunk;
	} else if ((0 == k)) {
	    __parsec_dtrsm_LLN_read_B0_parsec_assignment_t *target_locals =
		(__parsec_dtrsm_LLN_read_B0_parsec_assignment_t *) & generic_locals;
	    const int read_B0k = target_locals->k.value = k;
	    (void) read_B0k;
	    entry =
		data_repo_lookup_entry(read_B0_repo,
				       __jdf2c_make_key_read_B0((const parsec_taskpool_t *) __parsec_tp,
								(const parsec_assignment_t *) target_locals));
	    chunk = entry->data[0];	/* B:dtrsm <- B:read_B0 */
	    ACQUIRE_FLOW(this_task, "B", &dtrsm_LLN_read_B0, "B", target_locals, chunk);
	    this_task->data._f_B.data_out = chunk;
	}
	this_task->data._f_B.data_in = chunk;	/* flow B */
	this_task->data._f_B.data_repo = entry;
    } else {
	this_task->data._f_B.data_out = parsec_data_get_copy(chunk->original, target_device);
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(chunk->original, (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_dtrsm_for_B, 0);
#endif
    }
    this_task->data._f_A.data_out = NULL;	/* input only */

    if (NULL == (chunk = this_task->data._f_A.data_in)) {	/* flow A */
	entry = NULL;
	chunk = parsec_data_get_copy(data_of_descA(k, k), target_device);
	PARSEC_OBJ_RETAIN(chunk);
	this_task->data._f_A.data_out = chunk;
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(data_of_descA(k, k), (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_dtrsm_for_A,
				       1);
#endif
	this_task->data._f_A.data_in = chunk;	/* flow A */
	this_task->data._f_A.data_repo = entry;
    } else {
	this_task->data._f_A.data_out = parsec_data_get_copy(chunk->original, target_device);
#if defined(PARSEC_PROF_GRAPHER) && defined(PARSEC_PROF_TRACE)
	parsec_prof_grapher_data_input(chunk->original, (parsec_task_t *) this_task, &flow_of_dtrsm_LLN_dtrsm_for_A, 0);
#endif
    }
    /* ctl is a control flow */
    this_task->data._f_ctl.data_in = NULL;
    this_task->data._f_ctl.data_out = NULL;
    this_task->data._f_ctl.data_repo = NULL;
  /** Generate profiling information */
#if defined(PARSEC_PROF_TRACE)
    this_task->prof_info.desc = (parsec_data_collection_t *) __parsec_tp->super._g_descA;
    this_task->prof_info.data_id =
	((parsec_data_collection_t *) __parsec_tp->super._g_descA)->data_key((parsec_data_collection_t *) __parsec_tp->
									     super._g_descA, k, k);
    this_task->prof_info.task_class_id = this_task->task_class->task_class_id;
#endif /* defined(PARSEC_PROF_TRACE) */
    (void) k;
    (void) n;
    (void) chunk;
    (void) entry;

    return PARSEC_HOOK_RETURN_DONE;
}

static int datatype_lookup_of_dtrsm_LLN_dtrsm(parsec_execution_stream_t * es,
					      const __parsec_dtrsm_LLN_dtrsm_task_t * this_task, uint32_t * flow_mask,
					      parsec_dep_data_description_t * data)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    (void) __parsec_tp;
    (void) es;
    (void) this_task;
    (void) data;
    const int k = this_task->locals.k.value;
    (void) k;
    const int n = this_task->locals.n.value;
    (void) n;
    if ((*flow_mask) & 0x80000000U) {	/* these are the input flows */
	if ((*flow_mask) & 0x1U) {	/* Flow B */
	    if (((*flow_mask) & 0x1U)
		&& ((k >= 1) || (0 == k))) {
		data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
		data->layout = data->arena->opaque_dtt;
		data->count = 1;
		data->displ = 0;
		(*flow_mask) &= ~0x1U;
		return PARSEC_HOOK_RETURN_NEXT;
	    }
	}			/* (flow_mask & 0x1U) */
	if ((*flow_mask) & 0x2U) {	/* Flow A */
	    if (((*flow_mask) & 0x2U)) {	/* Have unconditional! */
		data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_FULL_ARENA];
		data->layout = data->arena->opaque_dtt;
		data->count = 1;
		data->displ = 0;
		(*flow_mask) &= ~0x2U;
		return PARSEC_HOOK_RETURN_NEXT;
	    }
	}			/* (flow_mask & 0x2U) */
	goto no_mask_match;
    }				/* input flows */
    if ((*flow_mask) & 0x3U) {	/* Flow B */
	if (((*flow_mask) & 0x3U)) {	/* Have unconditional! */
	    data->arena = __parsec_tp->super.arenas[PARSEC_dtrsm_LLN_VECTOR_ARENA];
	    data->layout = data->arena->opaque_dtt;
	    data->count = 1;
	    data->displ = 0;
	    (*flow_mask) &= ~0x3U;
	    return PARSEC_HOOK_RETURN_NEXT;
	}
    }				/* (flow_mask & 0x3U) */
  no_mask_match:
    data->arena = NULL;
    data->data = NULL;
    data->layout = PARSEC_DATATYPE_NULL;
    data->count = 0;
    data->displ = 0;
    (*flow_mask) = 0;		/* nothing left */
    (void) k;
    (void) n;
    return PARSEC_HOOK_RETURN_DONE;
}

static int hook_of_dtrsm_LLN_dtrsm(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dtrsm_task_t * this_task)
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    (void) es;
    (void) __parsec_tp;
    const int k = this_task->locals.k.value;
    (void) k;
    const int n = this_task->locals.n.value;
    (void) n;
    (void) k;
    (void) n;

  /** Declare the variables that will hold the data, and all the accounting for each */
    parsec_data_copy_t *_f_B = this_task->data._f_B.data_in;
    void *B = PARSEC_DATA_COPY_GET_PTR(_f_B);
    (void) B;
    parsec_data_copy_t *_f_A = this_task->data._f_A.data_in;
    void *A = PARSEC_DATA_COPY_GET_PTR(_f_A);
    (void) A;

  /** Update starting simulation date */
#if defined(PARSEC_SIM)
    {
	this_task->sim_exec_date = 0;
	data_repo_entry_t *eB = this_task->data._f_B.data_repo;
	if ((NULL != eB) && (eB->sim_exec_date > this_task->sim_exec_date))
	    this_task->sim_exec_date = eB->sim_exec_date;
	data_repo_entry_t *eA = this_task->data._f_A.data_repo;
	if ((NULL != eA) && (eA->sim_exec_date > this_task->sim_exec_date))
	    this_task->sim_exec_date = eA->sim_exec_date;
	if (this_task->task_class->sim_cost_fct != NULL) {
	    this_task->sim_exec_date += this_task->task_class->sim_cost_fct(this_task);
	}
	if (es->largest_simulation_date < this_task->sim_exec_date)
	    es->largest_simulation_date = this_task->sim_exec_date;
    }
#endif
  /** Transfer the ownership to the CPU */
#if defined(PARSEC_HAVE_CUDA)
    if (NULL != _f_B) {
	parsec_data_transfer_ownership_to_copy(_f_B->original, 0 /* device */ ,
					       PARSEC_FLOW_ACCESS_RW);
    }
#endif /* defined(PARSEC_HAVE_CUDA) */
  /** Cache Awareness Accounting */
#if defined(PARSEC_CACHE_AWARENESS)
    cache_buf_referenced(es->closest_cache, B);
    cache_buf_referenced(es->closest_cache, A);
#endif /* PARSEC_CACHE_AWARENESS */


#if !defined(PARSEC_PROF_DRY_BODY)

/*-----                                  dtrsm BODY                                  -----*/

    PARSEC_TASK_PROF_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id],
			   (parsec_task_t *) this_task);
#line 41 "dtrsm_LLN.jdf"
    {
#ifndef DRYRUN
	int tempkm = ((k) == (descB->mt - 1)) ? (descB->m - (k * descB->mb)) : descB->mb;
	int tempnn = ((n) == (descB->nt - 1)) ? (descB->n - (n * descB->nb)) : descB->nb;
	double lalpha = ((k) == (0)) ? (alpha) : (double) (1.0);
	int lda = BLKLDD(descA, k);
	int ldb = BLKLDD(descB, k);
//      double starttime, endtime;
//      starttime = MPI_Wtime();
	CORE_dtrsm(side, uplo, trans, diag, tempkm, tempnn, lalpha, A /* descA(k,k) */ , lda,
		   B /* descB(k,n) */ , ldb);
//      endtime   = MPI_Wtime();
//      printf("That took %f microseconds\n",1.e3*(endtime-starttime));
#endif
	if (k % 100 == 0)
	    fprintf(stderr, "DTRSM(%d) on node %d, NT=%d\n", k, descA->super.myrank, descB->mt);
	printlog("CORE_dtrsm(%d, %d)\n"
		 "\t(side, uplo, trans, diag, tempkm, tempnn, lalpha, descA(%d,%d)[%p], lda, descB(%d,%d)[%p], ldb)\n",
		 k, n, k, k, A, k, n, B);
    }

#line 4001 "dtrsm_LLN.c"
/*-----                              END OF dtrsm BODY                                -----*/



#endif /*!defined(PARSEC_PROF_DRY_BODY) */

    return PARSEC_HOOK_RETURN_DONE;
}

static int complete_hook_of_dtrsm_LLN_dtrsm(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dtrsm_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
#if defined(DISTRIBUTED)
    const int k = this_task->locals.k.value;
    (void) k;
    const int n = this_task->locals.n.value;
    (void) n;
#endif /* defined(DISTRIBUTED) */
    (void) es;
    (void) __parsec_tp;
    if (NULL != this_task->data._f_B.data_out) {
#if defined(PARSEC_DEBUG_NOISIER)
	char tmp[128];
#endif
	this_task->data._f_B.data_out->version++;	/* B */
	PARSEC_DEBUG_VERBOSE(10, parsec_debug_output,
			     "Complete hook of %s: change Data copy %p to version %d at %s:%d",
			     parsec_task_snprintf(tmp, 128, (parsec_task_t *) (this_task)),
			     this_task->data._f_B.data_out, this_task->data._f_B.data_out->version, __FILE__, __LINE__);
    }
    PARSEC_TASK_PROF_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id + 1],
			   (parsec_task_t *) this_task);
#if defined(DISTRIBUTED)
  /** If not working on distributed, there is no risk that data is not in place */
    (void) k;
    (void) n;

#endif /* DISTRIBUTED */
#if defined(PARSEC_PROF_GRAPHER)
    parsec_prof_grapher_task((parsec_task_t *) this_task, es->th_id, es->virtual_process->vp_id,
			     __jdf2c_key_fns_dtrsm.key_hash(this_task->task_class->
							    make_key((parsec_taskpool_t *) this_task->taskpool,
								     ((parsec_task_t *) this_task)->locals), NULL));
#endif /* defined(PARSEC_PROF_GRAPHER) */
    release_deps_of_dtrsm_LLN_dtrsm(es, this_task, PARSEC_ACTION_RELEASE_REMOTE_DEPS | PARSEC_ACTION_RELEASE_LOCAL_DEPS | PARSEC_ACTION_RELEASE_LOCAL_REFS | 0x7,	/* mask of all dep_index */
				    NULL);
    return PARSEC_HOOK_RETURN_DONE;
}

static parsec_hook_return_t release_task_of_dtrsm_LLN_dtrsm(parsec_execution_stream_t * es, parsec_task_t * this_task)
{
    const __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(const __parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    parsec_hash_table_t *ht = (parsec_hash_table_t *) __parsec_tp->super.super.dependencies_array[0];
    parsec_key_t key =
	this_task->task_class->make_key((const parsec_taskpool_t *) __parsec_tp,
					(const parsec_assignment_t *) &this_task->locals);
    parsec_hashable_dependency_t *hash_dep = (parsec_hashable_dependency_t *) parsec_hash_table_remove(ht, key);
    parsec_thread_mempool_free(hash_dep->mempool_owner, hash_dep);
    return parsec_release_task_to_mempool_update_nbtasks(es, this_task);
}

static char *dtrsm_LLN_dtrsm_LLN_dtrsm_internal_init_deps_key_functions_key_print(char *buffer, size_t buffer_size,
										  parsec_key_t __parsec_key_,
										  void *user_data)
{
    uint64_t __parsec_key = (uint64_t) (uintptr_t) __parsec_key_;
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp = (__parsec_dtrsm_LLN_internal_taskpool_t *) user_data;
    int k = (__parsec_key) % __parsec_tp->dtrsm_k_range;
    __parsec_key = __parsec_key / __parsec_tp->dtrsm_k_range;
    int n = (__parsec_key) % __parsec_tp->dtrsm_n_range;
    __parsec_key = __parsec_key / __parsec_tp->dtrsm_n_range;
    snprintf(buffer, buffer_size, "dtrsm(%d, %d)", k, n);
    return buffer;
}

static parsec_key_fn_t dtrsm_LLN_dtrsm_LLN_dtrsm_internal_init_deps_key_functions = {
    .key_equal = parsec_hash_table_generic_64bits_key_equal,
    .key_print = dtrsm_LLN_dtrsm_LLN_dtrsm_internal_init_deps_key_functions_key_print,
    .key_hash = parsec_hash_table_generic_64bits_key_hash
};

/* Needs: min-max count-tasks iterate */
static int dtrsm_LLN_dtrsm_internal_init(parsec_execution_stream_t * es, __parsec_dtrsm_LLN_dtrsm_task_t * this_task)
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) this_task->taskpool;
    int32_t nb_tasks = 0, saved_nb_tasks = 0;
    int32_t __k_min = 0x7fffffff, __k_max = 0;
    int32_t __jdf2c_k_min = 0x7fffffff, __jdf2c_k_max = 0;
    __parsec_dtrsm_LLN_dtrsm_parsec_assignment_t assignments;
    int32_t k, n;
    int32_t __jdf2c_k_start, __jdf2c_k_end, __jdf2c_k_inc;
#if defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
    PARSEC_PROFILING_TRACE(es->es_profile,
			   this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id],
			   0, this_task->taskpool->taskpool_id, NULL);
#endif /* defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
    __jdf2c_k_start = 0;
    __jdf2c_k_end = (descB->mt - 1);
    __jdf2c_k_inc = 1;
    __k_min = parsec_imin(__jdf2c_k_start, __jdf2c_k_end);
    __k_max = parsec_imax(__jdf2c_k_start, __jdf2c_k_end);
    __jdf2c_k_min = parsec_imin(__jdf2c_k_min, __k_min);
    __jdf2c_k_max = parsec_imax(__jdf2c_k_max, __k_max);
    for (k = __jdf2c_k_start; k <= __jdf2c_k_end; k += __jdf2c_k_inc) {
	assignments.k.value = k;
	{			/* block for the non-range variable n */
	    n = 0;
	    assignments.n.value = n;
	    if (!dtrsm_pred(k, n))
		continue;
	    nb_tasks++;
	}			/* block for the non-range variable n */
    }				/* Loop on normal range k */
    if (0 != nb_tasks) {
	(void) parsec_atomic_fetch_add_int32(&__parsec_tp->super.super.nb_tasks, nb_tasks);
    }
    saved_nb_tasks = nb_tasks;
    /* Set the range variables for the collision-free hash-computation */
    __parsec_tp->dtrsm_k_range = (__jdf2c_k_max - __jdf2c_k_min) + 1;
    __parsec_tp->dtrsm_n_range = 1;	/* single value, not a range */
    this_task->status = PARSEC_TASK_STATUS_COMPLETE;

    PARSEC_AYU_REGISTER_TASK(&dtrsm_LLN_dtrsm);
    __parsec_tp->super.super.dependencies_array[0] = PARSEC_OBJ_NEW(parsec_hash_table_t);
    parsec_hash_table_init(__parsec_tp->super.super.dependencies_array[0],
			   offsetof(parsec_hashable_dependency_t, ht_item), 10,
			   dtrsm_LLN_dtrsm_LLN_dtrsm_internal_init_deps_key_functions, this_task->taskpool);
    __parsec_tp->repositories[0] =
	data_repo_create_nothreadsafe(nb_tasks, __jdf2c_key_fns_dtrsm, (parsec_taskpool_t *) __parsec_tp, 3);
    (void) saved_nb_tasks;
    (void) __k_min;
    (void) __k_max;
    (void) __jdf2c_k_start;
    (void) __jdf2c_k_end;
    (void) __jdf2c_k_inc;
    (void) assignments;
    (void) __parsec_tp;
    (void) es;
    if (1 == parsec_atomic_fetch_dec_int32(&__parsec_tp->sync_point)) {
	/* Last initialization task complete. Update the number of tasks. */
	nb_tasks = parsec_atomic_fetch_dec_int32(&__parsec_tp->super.super.nb_tasks);
	parsec_mfence();	/* write memory barrier to guarantee that the scheduler gets the correct number of tasks */
	parsec_taskpool_enable((parsec_taskpool_t *) __parsec_tp, &__parsec_tp->startup_queue,
			       (parsec_task_t *) this_task, es, (1 <= nb_tasks));
#if defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
	PARSEC_PROFILING_TRACE(es->es_profile,
			       this_task->taskpool->profiling_array[2 * this_task->task_class->task_class_id + 1],
			       0, this_task->taskpool->taskpool_id, NULL);
#endif /* defined(PARSEC_PROF_TRACE) && defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
	return PARSEC_HOOK_RETURN_DONE;
    }
    return PARSEC_HOOK_RETURN_DONE;
}

static const __parsec_chore_t __dtrsm_LLN_dtrsm_chores[] = {
    {.type = PARSEC_DEV_CPU,
     .evaluate = NULL,
     .hook = (parsec_hook_t *) hook_of_dtrsm_LLN_dtrsm},
    {.type = PARSEC_DEV_NONE,
     .evaluate = NULL,
     .hook = (parsec_hook_t *) NULL},	/* End marker */
};

static const parsec_task_class_t dtrsm_LLN_dtrsm = {
    .name = "dtrsm",
    .task_class_id = 0,
    .nb_flows = 3,
    .nb_parameters = 2,
    .nb_locals = 2,
    .params = {&symb_dtrsm_LLN_dtrsm_k, &symb_dtrsm_LLN_dtrsm_n, NULL},
    .locals = {&symb_dtrsm_LLN_dtrsm_k, &symb_dtrsm_LLN_dtrsm_n, NULL},
    .data_affinity = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_dtrsm,
    .initial_data = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_dtrsm,
    .final_data = (parsec_data_ref_fn_t *) affinity_of_dtrsm_LLN_dtrsm,
    .priority = NULL,
    .properties = properties_of_dtrsm_LLN_dtrsm,
#if MAX_PARAM_COUNT < 2		/* number of read flows of dtrsm */
#error Too many read flows for task dtrsm
#endif /* MAX_PARAM_COUNT */
#if MAX_PARAM_COUNT < 1		/* number of write flows of dtrsm */
#error Too many write flows for task dtrsm
#endif /* MAX_PARAM_COUNT */
    .in = {&flow_of_dtrsm_LLN_dtrsm_for_B, &flow_of_dtrsm_LLN_dtrsm_for_A, NULL},
    .out = {&flow_of_dtrsm_LLN_dtrsm_for_B, &flow_of_dtrsm_LLN_dtrsm_for_ctl, NULL},
    .flags = 0x0 | PARSEC_HAS_IN_IN_DEPENDENCIES | PARSEC_USE_DEPS_MASK,
    .dependencies_goal = 0x3,
    .make_key = __jdf2c_make_key_dtrsm,
    .key_functions = &__jdf2c_key_fns_dtrsm,
    .fini = (parsec_hook_t *) NULL,
    .incarnations = __dtrsm_LLN_dtrsm_chores,
    .find_deps = parsec_hash_find_deps,
    .iterate_successors = (parsec_traverse_function_t *) iterate_successors_of_dtrsm_LLN_dtrsm,
    .iterate_predecessors = (parsec_traverse_function_t *) iterate_predecessors_of_dtrsm_LLN_dtrsm,
    .release_deps = (parsec_release_deps_t *) release_deps_of_dtrsm_LLN_dtrsm,
    .prepare_input = (parsec_hook_t *) data_lookup_of_dtrsm_LLN_dtrsm,
    .prepare_output = (parsec_hook_t *) NULL,
    .get_datatype = (parsec_datatype_lookup_t *) datatype_lookup_of_dtrsm_LLN_dtrsm,
    .complete_execution = (parsec_hook_t *) complete_hook_of_dtrsm_LLN_dtrsm,
    .release_task = &release_task_of_dtrsm_LLN_dtrsm,
#if defined(PARSEC_SIM)
    .sim_cost_fct = (parsec_sim_cost_fct_t *) NULL,
#endif
};


static const parsec_task_class_t *dtrsm_LLN_task_classes[] = {
    &dtrsm_LLN_dtrsm,
    &dtrsm_LLN_read_B0,
    &dtrsm_LLN_write_B0,
    &dtrsm_LLN_dgemm
};

static void dtrsm_LLN_startup(parsec_context_t * context, __parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp,
			      parsec_list_item_t ** ready_tasks)
{
    uint32_t i, supported_dev = 0;

    for (i = 0; i < parsec_nb_devices; i++) {
	if (!(__parsec_tp->super.super.devices_index_mask & (1 << i)))
	    continue;
	parsec_device_module_t *device = parsec_mca_device_get(i);
	parsec_data_collection_t *parsec_dc;

	if (NULL == device)
	    continue;
	if (NULL != device->taskpool_register)
	    if (PARSEC_SUCCESS != device->taskpool_register(device, (parsec_taskpool_t *) __parsec_tp)) {
		parsec_debug_verbose(5, parsec_debug_output, "Device %s refused to register taskpool %p", device->name,
				     __parsec_tp);
		__parsec_tp->super.super.devices_index_mask &= ~(1 << device->device_index);
		continue;
	    }
	if (NULL != device->memory_register) {	/* Register all the data */
	    parsec_dc = (parsec_data_collection_t *) __parsec_tp->super._g_descA;
	    if ((NULL != parsec_dc->register_memory) &&
		(PARSEC_SUCCESS != parsec_dc->register_memory(parsec_dc, device))) {
		parsec_debug_verbose(3, parsec_debug_output,
				     "Device %s refused to register memory for data %s (%p) from taskpool %p",
				     device->name, parsec_dc->key_base, parsec_dc, __parsec_tp);
		__parsec_tp->super.super.devices_index_mask &= ~(1 << device->device_index);
	    }
	    parsec_dc = (parsec_data_collection_t *) __parsec_tp->super._g_descB;
	    if ((NULL != parsec_dc->register_memory) &&
		(PARSEC_SUCCESS != parsec_dc->register_memory(parsec_dc, device))) {
		parsec_debug_verbose(3, parsec_debug_output,
				     "Device %s refused to register memory for data %s (%p) from taskpool %p",
				     device->name, parsec_dc->key_base, parsec_dc, __parsec_tp);
		__parsec_tp->super.super.devices_index_mask &= ~(1 << device->device_index);
	    }
	}
	supported_dev |= device->type;
    }
    /* Remove all the chores without a backend device */
    for (i = 0; i < PARSEC_dtrsm_LLN_NB_TASK_CLASSES; i++) {
	parsec_task_class_t *tc = (parsec_task_class_t *) __parsec_tp->super.super.task_classes_array[i];
	__parsec_chore_t *chores = (__parsec_chore_t *) tc->incarnations;
	uint32_t idx = 0, j;
	for (j = 0; NULL != chores[j].hook; j++) {
	    if (!(supported_dev & chores[j].type))
		continue;
	    if (j != idx) {
		chores[idx] = chores[j];
		parsec_debug_verbose(20, parsec_debug_output, "Device type %i disabledfor function %s", chores[j].type,
				     tc->name);
	    }
	    idx++;
	}
	chores[idx].type = PARSEC_DEV_NONE;
	chores[idx].evaluate = NULL;
	chores[idx].hook = NULL;
	parsec_task_t *task =
	    (parsec_task_t *) parsec_thread_mempool_allocate(context->virtual_processes[0]->execution_streams[0]->
							     context_mempool);
	task->taskpool = (parsec_taskpool_t *) __parsec_tp;
	task->chore_id = 0;
	task->status = PARSEC_TASK_STATUS_NONE;
	memset(&task->locals, 0, sizeof(parsec_assignment_t) * MAX_LOCAL_COUNT);
	PARSEC_LIST_ITEM_SINGLETON(task);
	task->priority = -1;
	task->task_class = task->taskpool->task_classes_array[PARSEC_dtrsm_LLN_NB_TASK_CLASSES + i];
	int where = i % context->nb_vp;
	if (NULL == ready_tasks[where])
	    ready_tasks[where] = &task->super;
	else
	    ready_tasks[where] = parsec_list_item_ring_push(ready_tasks[where], &task->super);
    }
}

static void dtrsm_LLN_destructor(__parsec_dtrsm_LLN_internal_taskpool_t * __parsec_tp)
{
    uint32_t i;
    parsec_taskpool_unregister(&__parsec_tp->super.super);
    for (i = 0; i < (uint32_t) (2 * __parsec_tp->super.super.nb_task_classes); i++) {	/* Extra startup function added at the end */
	parsec_task_class_t *tc = (parsec_task_class_t *) __parsec_tp->super.super.task_classes_array[i];
	free((void *) tc->incarnations);
	free(tc);
    }
    free(__parsec_tp->super.super.task_classes_array);
    __parsec_tp->super.super.task_classes_array = NULL;
    __parsec_tp->super.super.nb_task_classes = 0;

    for (i = 0; i < (uint32_t) __parsec_tp->super.arenas_size; i++) {
	if (__parsec_tp->super.arenas[i] != NULL) {
	    parsec_arena_destruct(__parsec_tp->super.arenas[i]);
	    free(__parsec_tp->super.arenas[i]);
	    __parsec_tp->super.arenas[i] = NULL;
	}
    }
    free(__parsec_tp->super.arenas);
    __parsec_tp->super.arenas = NULL;
    __parsec_tp->super.arenas_size = 0;
    /* Destroy the data repositories for this object */
    data_repo_destroy_nothreadsafe(__parsec_tp->repositories[3]);	/* dgemm */
    data_repo_destroy_nothreadsafe(__parsec_tp->repositories[1]);	/* read_B0 */
    data_repo_destroy_nothreadsafe(__parsec_tp->repositories[0]);	/* dtrsm */
    /* Release the dependencies arrays for this object */
    parsec_hash_table_fini((parsec_hash_table_t *) __parsec_tp->super.super.dependencies_array[3]);
    PARSEC_OBJ_RELEASE(__parsec_tp->super.super.dependencies_array[3]);
    __parsec_tp->super.super.dependencies_array[3] = NULL;
    parsec_hash_table_fini((parsec_hash_table_t *) __parsec_tp->super.super.dependencies_array[2]);
    PARSEC_OBJ_RELEASE(__parsec_tp->super.super.dependencies_array[2]);
    __parsec_tp->super.super.dependencies_array[2] = NULL;
    parsec_hash_table_fini((parsec_hash_table_t *) __parsec_tp->super.super.dependencies_array[1]);
    PARSEC_OBJ_RELEASE(__parsec_tp->super.super.dependencies_array[1]);
    __parsec_tp->super.super.dependencies_array[1] = NULL;
    parsec_hash_table_fini((parsec_hash_table_t *) __parsec_tp->super.super.dependencies_array[0]);
    PARSEC_OBJ_RELEASE(__parsec_tp->super.super.dependencies_array[0]);
    __parsec_tp->super.super.dependencies_array[0] = NULL;
    free(__parsec_tp->super.super.dependencies_array);
    __parsec_tp->super.super.dependencies_array = NULL;
    /* Unregister all the data */
    uint32_t _i;
    for (_i = 0; _i < parsec_nb_devices; _i++) {
	parsec_device_module_t *device;
	parsec_data_collection_t *parsec_dc;
	if (!(__parsec_tp->super.super.devices_index_mask & (1 << _i)))
	    continue;
	if ((NULL == (device = parsec_mca_device_get(_i))) || (NULL == device->memory_unregister))
	    continue;
	parsec_dc = (parsec_data_collection_t *) __parsec_tp->super._g_descA;
	if (NULL != parsec_dc->unregister_memory) {
	    (void) parsec_dc->unregister_memory(parsec_dc, device);
	};
	parsec_dc = (parsec_data_collection_t *) __parsec_tp->super._g_descB;
	if (NULL != parsec_dc->unregister_memory) {
	    (void) parsec_dc->unregister_memory(parsec_dc, device);
	};
    }
    /* Unregister the taskpool from the devices */
    for (i = 0; i < parsec_nb_devices; i++) {
	if (!(__parsec_tp->super.super.devices_index_mask & (1 << i)))
	    continue;
	__parsec_tp->super.super.devices_index_mask ^= (1 << i);
	parsec_device_module_t *device = parsec_mca_device_get(i);
	if ((NULL == device) || (NULL == device->taskpool_unregister))
	    continue;
	if (PARSEC_SUCCESS != device->taskpool_unregister(device, &__parsec_tp->super.super))
	    continue;
    }
    free(__parsec_tp->super.super.taskpool_name);
    free(__parsec_tp);
}

#undef side
#undef uplo
#undef trans
#undef diag
#undef alpha
#undef descA
#undef descB

parsec_dtrsm_LLN_taskpool_t *parsec_dtrsm_LLN_new(dplasma_enum_t side, dplasma_enum_t uplo, dplasma_enum_t trans,
						  dplasma_enum_t diag, double alpha,
						  const parsec_tiled_matrix_dc_t * descA /* data descA */ ,
						  parsec_tiled_matrix_dc_t * descB /* data descB */ )
{
    __parsec_dtrsm_LLN_internal_taskpool_t *__parsec_tp =
	(__parsec_dtrsm_LLN_internal_taskpool_t *) calloc(1, sizeof(__parsec_dtrsm_LLN_internal_taskpool_t));
    parsec_task_class_t *tc;
    uint32_t i, j;
    /* Dump the hidden parameters with default values */

    __parsec_tp->super.super.nb_task_classes = PARSEC_dtrsm_LLN_NB_TASK_CLASSES;
    __parsec_tp->super.super.devices_index_mask = PARSEC_DEVICES_ALL;
    __parsec_tp->super.super.taskpool_name = strdup("dtrsm_LLN");
    __parsec_tp->super.super.update_nb_runtime_task = parsec_add_fetch_runtime_task;
    __parsec_tp->super.super.dependencies_array = (void **)
	calloc(__parsec_tp->super.super.nb_task_classes, sizeof(void *));
    /* Twice the size to hold the startup tasks function_t */
    __parsec_tp->super.super.task_classes_array = (const parsec_task_class_t **)
	malloc(2 * __parsec_tp->super.super.nb_task_classes * sizeof(parsec_task_class_t *));
    __parsec_tp->super.super.nb_tasks = 1;
    __parsec_tp->super.super.taskpool_type = PARSEC_TASKPOOL_TYPE_PTG;
    __parsec_tp->super.super.nb_pending_actions = 1 + __parsec_tp->super.super.nb_task_classes;	/* for the startup tasks */
    __parsec_tp->sync_point = __parsec_tp->super.super.nb_task_classes;
    __parsec_tp->startup_queue = NULL;
    for (i = 0; i < __parsec_tp->super.super.nb_task_classes; i++) {
	__parsec_tp->super.super.task_classes_array[i] = tc = malloc(sizeof(parsec_task_class_t));
	memcpy(tc, dtrsm_LLN_task_classes[i], sizeof(parsec_task_class_t));
	for (j = 0; NULL != tc->incarnations[j].hook; j++);	/* compute the number of incarnations */
	tc->incarnations = (__parsec_chore_t *) malloc((j + 1) * sizeof(__parsec_chore_t));
	memcpy((__parsec_chore_t *) tc->incarnations, dtrsm_LLN_task_classes[i]->incarnations,
	       (j + 1) * sizeof(__parsec_chore_t));

	/* Add a placeholder for initialization and startup task */
	__parsec_tp->super.super.task_classes_array[__parsec_tp->super.super.nb_task_classes + i] = tc =
	    (parsec_task_class_t *) malloc(sizeof(parsec_task_class_t));
	memcpy(tc, (void *) &__parsec_generic_startup, sizeof(parsec_task_class_t));
	tc->task_class_id = __parsec_tp->super.super.nb_task_classes + i;
	tc->incarnations = (__parsec_chore_t *) malloc(2 * sizeof(__parsec_chore_t));
	memcpy((__parsec_chore_t *) tc->incarnations, (void *) __parsec_generic_startup.incarnations,
	       2 * sizeof(__parsec_chore_t));
	tc->release_task = parsec_release_task_to_mempool_and_count_as_runtime_tasks;
    }
    /* Startup task for dgemm */
    tc = (parsec_task_class_t *) __parsec_tp->super.super.task_classes_array[__parsec_tp->super.super.nb_task_classes +
									     0];
    tc->name = "Startup for dgemm";
    tc->prepare_input = (parsec_hook_t *) dtrsm_LLN_dgemm_internal_init;
    /* Startup task for write_B0 */
    tc = (parsec_task_class_t *) __parsec_tp->super.super.task_classes_array[__parsec_tp->super.super.nb_task_classes +
									     1];
    tc->name = "Startup for write_B0";
    tc->prepare_input = (parsec_hook_t *) dtrsm_LLN_write_B0_internal_init;
    /* Startup task for read_B0 */
    tc = (parsec_task_class_t *) __parsec_tp->super.super.task_classes_array[__parsec_tp->super.super.nb_task_classes +
									     2];
    tc->name = "Startup for read_B0";
    tc->prepare_input = (parsec_hook_t *) dtrsm_LLN_read_B0_internal_init;
    ((__parsec_chore_t *) & tc->incarnations[0])->hook = (parsec_hook_t *) __jdf2c_startup_read_B0;
    /* Startup task for dtrsm */
    tc = (parsec_task_class_t *) __parsec_tp->super.super.task_classes_array[__parsec_tp->super.super.nb_task_classes +
									     3];
    tc->name = "Startup for dtrsm";
    tc->prepare_input = (parsec_hook_t *) dtrsm_LLN_dtrsm_internal_init;
    /* Compute the number of arenas: */
    /*   PARSEC_dtrsm_LLN_FULL_ARENA  ->  0 */
    /*   PARSEC_dtrsm_LLN_VECTOR_ARENA  ->  1 */
    /*   PARSEC_dtrsm_LLN_DEFAULT_ARENA  ->  2 */
    __parsec_tp->super.arenas_size = 3;
    __parsec_tp->super.arenas = (parsec_arena_t **) malloc(__parsec_tp->super.arenas_size * sizeof(parsec_arena_t *));
    for (i = 0; i < __parsec_tp->super.arenas_size; i++) {
	__parsec_tp->super.arenas[i] = (parsec_arena_t *) calloc(1, sizeof(parsec_arena_t));
    }
    /* Now the Parameter-dependent structures: */
    __parsec_tp->super._g_side = side;
    __parsec_tp->super._g_uplo = uplo;
    __parsec_tp->super._g_trans = trans;
    __parsec_tp->super._g_diag = diag;
    __parsec_tp->super._g_alpha = alpha;
    __parsec_tp->super._g_descA = descA;
    __parsec_tp->super._g_descB = descB;
    /* If profiling is enabled, the keys for profiling */
#if defined(PARSEC_PROF_TRACE)
    __parsec_tp->super.super.profiling_array = dtrsm_LLN_profiling_array;
    if (-1 == dtrsm_LLN_profiling_array[0]) {
#if defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
	parsec_profiling_add_dictionary_keyword("dgemm (internal init)", "fill:34D8D8",
						0,
						NULL,
						(int *) &__parsec_tp->super.super.profiling_array[0 +
												  2 *
												  dtrsm_LLN_dgemm.
												  task_class_id +
												  2 *
												  PARSEC_dtrsm_LLN_NB_TASK_CLASSES
												  /* dgemm (internal init) start key */
												  ],
						(int *) &__parsec_tp->super.super.profiling_array[1 +
												  2 *
												  dtrsm_LLN_dgemm.
												  task_class_id +
												  2 *
												  PARSEC_dtrsm_LLN_NB_TASK_CLASSES
												  /* dgemm (internal init) end key */
												  ]);
#endif /* defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
	parsec_profiling_add_dictionary_keyword("dgemm", "fill:CC2828",
						sizeof(parsec_task_prof_info_t) + 3 * sizeof(parsec_assignment_t),
						"dc_key{uint64_t};dc_dataid{uint32_t};tcid{int32_t};k{int32_t};m{int32_t};n{int32_t}",
						(int *) &__parsec_tp->super.super.profiling_array[0 +
												  2 *
												  dtrsm_LLN_dgemm.
												  task_class_id
												  /* dgemm start key */
												  ],
						(int *) &__parsec_tp->super.super.profiling_array[1 +
												  2 *
												  dtrsm_LLN_dgemm.
												  task_class_id
												  /* dgemm end key */
												  ]);

#if defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
	parsec_profiling_add_dictionary_keyword("write_B0 (internal init)", "fill:8634D8",
						0,
						NULL,
						(int *) &__parsec_tp->super.super.profiling_array[0 +
												  2 *
												  dtrsm_LLN_write_B0.
												  task_class_id +
												  2 *
												  PARSEC_dtrsm_LLN_NB_TASK_CLASSES
												  /* write_B0 (internal init) start key */
												  ],
						(int *) &__parsec_tp->super.super.profiling_array[1 +
												  2 *
												  dtrsm_LLN_write_B0.
												  task_class_id +
												  2 *
												  PARSEC_dtrsm_LLN_NB_TASK_CLASSES
												  /* write_B0 (internal init) end key */
												  ]);
#endif /* defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
	parsec_profiling_add_dictionary_keyword("write_B0", "fill:7ACC28",
						sizeof(parsec_task_prof_info_t) + 1 * sizeof(parsec_assignment_t),
						"dc_key{uint64_t};dc_dataid{uint32_t};tcid{int32_t};k{int32_t}",
						(int *) &__parsec_tp->super.super.profiling_array[0 +
												  2 *
												  dtrsm_LLN_write_B0.
												  task_class_id
												  /* write_B0 start key */
												  ],
						(int *) &__parsec_tp->super.super.profiling_array[1 +
												  2 *
												  dtrsm_LLN_write_B0.
												  task_class_id
												  /* write_B0 end key */
												  ]);

#if defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
	parsec_profiling_add_dictionary_keyword("read_B0 (internal init)", "fill:D83434",
						0,
						NULL,
						(int *) &__parsec_tp->super.super.profiling_array[0 +
												  2 *
												  dtrsm_LLN_read_B0.
												  task_class_id +
												  2 *
												  PARSEC_dtrsm_LLN_NB_TASK_CLASSES
												  /* read_B0 (internal init) start key */
												  ],
						(int *) &__parsec_tp->super.super.profiling_array[1 +
												  2 *
												  dtrsm_LLN_read_B0.
												  task_class_id +
												  2 *
												  PARSEC_dtrsm_LLN_NB_TASK_CLASSES
												  /* read_B0 (internal init) end key */
												  ]);
#endif /* defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
	parsec_profiling_add_dictionary_keyword("read_B0", "fill:28CCCC",
						sizeof(parsec_task_prof_info_t) + 1 * sizeof(parsec_assignment_t),
						"dc_key{uint64_t};dc_dataid{uint32_t};tcid{int32_t};k{int32_t}",
						(int *) &__parsec_tp->super.super.profiling_array[0 +
												  2 *
												  dtrsm_LLN_read_B0.
												  task_class_id
												  /* read_B0 start key */
												  ],
						(int *) &__parsec_tp->super.super.profiling_array[1 +
												  2 *
												  dtrsm_LLN_read_B0.
												  task_class_id
												  /* read_B0 end key */
												  ]);

#if defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT)
	parsec_profiling_add_dictionary_keyword("dtrsm (internal init)", "fill:86D834",
						0,
						NULL,
						(int *) &__parsec_tp->super.super.profiling_array[0 +
												  2 *
												  dtrsm_LLN_dtrsm.
												  task_class_id +
												  2 *
												  PARSEC_dtrsm_LLN_NB_TASK_CLASSES
												  /* dtrsm (internal init) start key */
												  ],
						(int *) &__parsec_tp->super.super.profiling_array[1 +
												  2 *
												  dtrsm_LLN_dtrsm.
												  task_class_id +
												  2 *
												  PARSEC_dtrsm_LLN_NB_TASK_CLASSES
												  /* dtrsm (internal init) end key */
												  ]);
#endif /* defined(PARSEC_PROF_TRACE_PTG_INTERNAL_INIT) */
	parsec_profiling_add_dictionary_keyword("dtrsm", "fill:7A28CC",
						sizeof(parsec_task_prof_info_t) + 2 * sizeof(parsec_assignment_t),
						"dc_key{uint64_t};dc_dataid{uint32_t};tcid{int32_t};k{int32_t};n{int32_t}",
						(int *) &__parsec_tp->super.super.profiling_array[0 +
												  2 *
												  dtrsm_LLN_dtrsm.
												  task_class_id
												  /* dtrsm start key */
												  ],
						(int *) &__parsec_tp->super.super.profiling_array[1 +
												  2 *
												  dtrsm_LLN_dtrsm.
												  task_class_id
												  /* dtrsm end key */
												  ]);

    }
#endif /* defined(PARSEC_PROF_TRACE) */
    PARSEC_AYU_REGISTER_TASK(&dtrsm_LLN_dgemm);
    PARSEC_AYU_REGISTER_TASK(&dtrsm_LLN_write_B0);
    PARSEC_AYU_REGISTER_TASK(&dtrsm_LLN_read_B0);
    PARSEC_AYU_REGISTER_TASK(&dtrsm_LLN_dtrsm);
    __parsec_tp->super.super.repo_array = __parsec_tp->repositories;
    __parsec_tp->super.super.startup_hook = (parsec_startup_fn_t) dtrsm_LLN_startup;
    __parsec_tp->super.super.destructor = (parsec_destruct_fn_t) dtrsm_LLN_destructor;
    (void) parsec_taskpool_reserve_id((parsec_taskpool_t *) __parsec_tp);
/* Prevent warnings related to not used hidden global variables */
    ;
    return (parsec_dtrsm_LLN_taskpool_t *) __parsec_tp;
}
