#ifndef _ASM_GENERIC_ATOMIC_LONG_H
#define _ASM_GENERIC_ATOMIC_LONG_H
/*
 * Copyright (C) 2005 Silicon Graphics, Inc.
 *	Christoph Lameter
 *
 * Allows to provide arch independent atomic definitions without the need to
 * edit all arch specific atomic.h files.
 */

#include <asm/types.h>
#ifdef CONFIG_GENERIC_ATOMIC64
#include <asm-generic/atomic64.h>
#endif

/*
 * Suppport for atomic_long_t
 *
 * Casts for parameters are avoided for existing atomic functions in order to
 * avoid issues with cast-as-lval under gcc 4.x and other limitations that the
 * macros of a platform may have.
 */

#if BITS_PER_LONG == 64

typedef atomic64_t atomic_long_t;

#define ATOMIC_LONG_INIT(i)	ATOMIC64_INIT(i)

static inline long atomic_long_read(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_read(v);
}

static inline void atomic_long_set(atomic_long_t *l, long i)
{
	atomic64_t *v = (atomic64_t *)l;

	atomic64_set(v, i);
}

static inline void atomic_long_inc(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	atomic64_inc(v);
}

static inline void atomic_long_dec(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	atomic64_dec(v);
}

static inline void atomic_long_add(long i, atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	atomic64_add(i, v);
}

static inline void atomic_long_sub(long i, atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	atomic64_sub(i, v);
}

static inline int atomic_long_sub_and_test(long i, atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return atomic64_sub_and_test(i, v);
}

static inline int atomic_long_dec_and_test(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return atomic64_dec_and_test(v);
}

static inline int atomic_long_inc_and_test(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return atomic64_inc_and_test(v);
}

static inline int atomic_long_add_negative(long i, atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return atomic64_add_negative(i, v);
}

static inline long atomic_long_add_return(long i, atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_add_return(i, v);
}

static inline long atomic_long_sub_return(long i, atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_sub_return(i, v);
}

static inline long atomic_long_inc_return(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_inc_return(v);
}

static inline long atomic_long_dec_return(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_dec_return(v);
}

static inline long atomic_long_add_unless(atomic_long_t *l, long a, long u)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_add_unless(v, a, u);
}

#define atomic_long_inc_not_zero(l) atomic64_inc_not_zero((atomic64_t *)(l))

#define atomic_long_cmpxchg(l, old, new) \
	(atomic64_cmpxchg((atomic64_t *)(l), (old), (new)))
#define atomic_long_xchg(v, new) \
	(atomic64_xchg((atomic64_t *)(v), (new)))

#else  /*  BITS_PER_LONG == 64  */

typedef atomic_t atomic_long_t;

#define ATOMIC_LONG_INIT(i)	ATOMIC_INIT(i)
static inline long atomic_long_read(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return (long)atomic_read(v);
}

static inline void atomic_long_set(atomic_long_t *l, long i)
{
	atomic_t *v = (atomic_t *)l;

	atomic_set(v, i);
}

static inline void atomic_long_inc(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	atomic_inc(v);
}

static inline void atomic_long_dec(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	atomic_dec(v);
}

#define ATOMIC_LONG_OP(op)						\
static inline void							\
atomic_long_##op(long i, atomic_long_t *l)				\
{									\
	ATOMIC_LONG_PFX(_t) *v = (ATOMIC_LONG_PFX(_t) *)l;		\
									\
	ATOMIC_LONG_PFX(_##op)(i, v);					\
}

ATOMIC_LONG_OP(add)
ATOMIC_LONG_OP(sub)
ATOMIC_LONG_OP(and)
ATOMIC_LONG_OP(or)
ATOMIC_LONG_OP(xor)
ATOMIC_LONG_OP(andnot)

#undef ATOMIC_LONG_OP

static inline int atomic_long_sub_and_test(long i, atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return atomic_sub_and_test(i, v);
}

static inline int atomic_long_dec_and_test(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return atomic_dec_and_test(v);
}

static inline int atomic_long_inc_and_test(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return atomic_inc_and_test(v);
}

static inline int atomic_long_add_negative(long i, atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return atomic_add_negative(i, v);
}

static inline long atomic_long_add_return(long i, atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return (long)atomic_add_return(i, v);
}

static inline long atomic_long_sub_return(long i, atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return (long)atomic_sub_return(i, v);
}

#define ATOMIC_LONG_INC_DEC_OP(op, mo)					\
static inline long							\
atomic_long_##op##_return##mo(atomic_long_t *l)				\
{									\
	ATOMIC_LONG_PFX(_t) *v = (ATOMIC_LONG_PFX(_t) *)l;		\
									\
	return (long)ATOMIC_LONG_PFX(_##op##_return##mo)(v);		\
}
ATOMIC_LONG_INC_DEC_OP(inc,)
ATOMIC_LONG_INC_DEC_OP(inc, _relaxed)
ATOMIC_LONG_INC_DEC_OP(inc, _acquire)
ATOMIC_LONG_INC_DEC_OP(inc, _release)
ATOMIC_LONG_INC_DEC_OP(dec,)
ATOMIC_LONG_INC_DEC_OP(dec, _relaxed)
ATOMIC_LONG_INC_DEC_OP(dec, _acquire)
ATOMIC_LONG_INC_DEC_OP(dec, _release)

#undef ATOMIC_LONG_INC_DEC_OP

static inline long atomic_long_add_unless(atomic_long_t *l, long a, long u)
{
	atomic_t *v = (atomic_t *)l;

	return (long)atomic_add_unless(v, a, u);
}

#define atomic_long_inc_not_zero(l) atomic_inc_not_zero((atomic_t *)(l))

#define atomic_long_cmpxchg(l, old, new) \
	(atomic_cmpxchg((atomic_t *)(l), (old), (new)))
#define atomic_long_xchg(v, new) \
	(atomic_xchg((atomic_t *)(v), (new)))

#endif  /*  BITS_PER_LONG == 64  */

#define atomic_long_cond_read_relaxed(v, c) \
	ATOMIC_LONG_PFX(_cond_read_relaxed)((ATOMIC_LONG_PFX(_t) *)(v), (c))
#define atomic_long_cond_read_acquire(v, c) \
	ATOMIC_LONG_PFX(_cond_read_acquire)((ATOMIC_LONG_PFX(_t) *)(v), (c))

#endif  /*  _ASM_GENERIC_ATOMIC_LONG_H  */
