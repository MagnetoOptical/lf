/*
 * LF: Global Fully Replicated Key/Value Store
 * Copyright (C) 2018-2019  ZeroTier, Inc.  https://www.zerotier.com/
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * --
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial closed-source software that incorporates or links
 * directly against ZeroTier software without disclosing the source code
 * of your own application.
 */

#ifndef ZTLF_ISET_H
#define ZTLF_ISET_H

#include "common.h"
#include "vector.h"

#define ZTLF_ISET_BUCKET_COUNT 4194304

/**
 * A fast integer set with a currently fixed number of buckets
 */
struct ZTLF_ISet { struct ZTLF_Vector_i64 buckets[ZTLF_ISET_BUCKET_COUNT]; };

static inline struct ZTLF_ISet *ZTLF_ISet_New()
{
	struct ZTLF_ISet *s;
	ZTLF_MALLOC_CHECK(s = (struct ZTLF_ISet *)malloc(sizeof(struct ZTLF_ISet)));
	memset(s,0,sizeof(struct ZTLF_ISet));
	return s;
}

static inline void ZTLF_ISet_Free(struct ZTLF_ISet *s)
{
	for(unsigned long k=0;k<ZTLF_ISET_BUCKET_COUNT;++k) {
		ZTLF_Vector_i64_Free(s->buckets + k);
	}
	free(s);
}

static inline void ZTLF_ISet_Clear(struct ZTLF_ISet *s)
{
	for(unsigned long k=0;k<ZTLF_ISET_BUCKET_COUNT;++k) {
		ZTLF_Vector_i64_Clear(s->buckets + k);
	}
}

static inline bool ZTLF_ISet_Put(struct ZTLF_ISet *s,const int64_t i)
{
	struct ZTLF_Vector_i64 *const v = s->buckets + ((unsigned long)(0x9e3779b97f4a7c13ULL * (uint64_t)i) % ZTLF_ISET_BUCKET_COUNT);
	for(unsigned long k=0;k<v->size;k++) {
		if (v->v[k] == i)
			return false;
	}
	ZTLF_Vector_i64_Append(v,i);
	return true;
}

static inline bool ZTLF_ISet_Contains(struct ZTLF_ISet *s,const int64_t i)
{
	struct ZTLF_Vector_i64 *const v = s->buckets + ((unsigned long)(0x9e3779b97f4a7c13ULL * (uint64_t)i) % ZTLF_ISET_BUCKET_COUNT);
	for(unsigned long k=0;k<v->size;k++) {
		if (v->v[k] == i)
			return true;
	}
	return false;
}

#endif
