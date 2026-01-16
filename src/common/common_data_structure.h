// FileName: common_data_structure.h
// Copyright (c) 2025 Wonjin Kim. All rights reserved.

#ifndef COMMON_DATA_STRUCTURE_H
#define COMMON_DATA_STRUCTURE_H

#ifndef CheckNull
	#define CheckNull(p) ((p) == 0)
#endif

#ifndef SetNull
	#define SetNull(p) ((p) = 0)
#endif

// --- Stack ---
#define StackPushN(f, n, next) \
	do                         \
	{                          \
		(n)->next = (f);       \
		(f)       = (n);       \
	}                          \
	while (0)

#define StackPopNZ(f, next, zchk) \
	do                            \
	{                             \
		if (!zchk(f))             \
			(f) = (f)->next;      \
	}                             \
	while (0)

// --- Queue ---
#define QueuePushNZ(f, l, n, next, zchk, zset) \
	do                                         \
	{                                          \
		if (zchk(f))                           \
		{                                      \
			(f) = (l) = (n);                   \
			zset((n)->next);                   \
		}                                      \
		else                                   \
		{                                      \
			(l)->next = (n);                   \
			(l)       = (n);                   \
			zset((n)->next);                   \
		}                                      \
	}                                          \
	while (0)

#define QueuePushFrontNZ(f, l, n, next, zchk, zset) \
	do                                              \
	{                                               \
		if (zchk(f))                                \
		{                                           \
			(f) = (l) = (n);                        \
			zset((n)->next);                        \
		}                                           \
		else                                        \
		{                                           \
			(n)->next = (f);                        \
			(f)       = (n);                        \
		}                                           \
	}                                               \
	while (0)

#define QueuePopNZ(f, l, next, zset) \
	do                               \
	{                                \
		if ((f) == (l))              \
		{                            \
			zset(f);                 \
			zset(l);                 \
		}                            \
		else                         \
		{                            \
			(f) = (f)->next;         \
		}                            \
	}                                \
	while (0)

// --- Doubly Linked List ---
#define DLLInsertNPZ(f, l, p, n, next, prev, zchk, zset) \
	do                                                   \
	{                                                    \
		if (zchk(f))                                     \
		{                                                \
			(f) = (l) = (n);                             \
			zset((n)->next);                             \
			zset((n)->prev);                             \
		}                                                \
		else if (zchk(p))                                \
		{                                                \
			zset((n)->prev);                             \
			(n)->next = (f);                             \
			if (!zchk(f))                                \
				(f)->prev = (n);                         \
			(f) = (n);                                   \
		}                                                \
		else                                             \
		{                                                \
			if (!zchk((p)->next))                        \
				(p)->next->prev = (n);                   \
			(n)->next = (p)->next;                       \
			(n)->prev = (p);                             \
			(p)->next = (n);                             \
			if ((p) == (l))                              \
				(l) = (n);                               \
		}                                                \
	}                                                    \
	while (0)

#define DLLPushBackNPZ(f, l, n, next, prev, zchk, zset) \
	DLLInsertNPZ(f, l, l, n, next, prev, zchk, zset)

#define DLLRemoveNPZ(f, l, n, next, prev, zchk, zset) \
	do                                                \
	{                                                 \
		if ((f) == (n))                               \
		{                                             \
			(f) = (f)->next;                          \
			if (zchk(f))                              \
				zset(l);                              \
			else                                      \
				zset((f)->prev);                      \
		}                                             \
		else if ((l) == (n))                          \
		{                                             \
			(l) = (l)->prev;                          \
			if (zchk(l))                              \
				zset(f);                              \
			else                                      \
				zset((l)->next);                      \
		}                                             \
		else                                          \
		{                                             \
			if (!zchk((n)->next))                     \
				(n)->next->prev = (n)->prev;          \
			if (!zchk((n)->prev))                     \
				(n)->prev->next = (n)->next;          \
		}                                             \
	}                                                 \
	while (0)

// --- User-friendly aliases ---
#define QueuePush(f, l, n)      QueuePushNZ(f, l, n, next, CheckNull, SetNull)
#define QueuePushFront(f, l, n) QueuePushFrontNZ(f, l, n, next, CheckNull, SetNull)
#define QueuePop(f, l)          QueuePopNZ(f, l, next, SetNull)

#define StackPush(f, n) StackPushN(f, n, next)
#define StackPop(f)     StackPopNZ(f, next, CheckNull)

#define DLLPushBack(f, l, n)  DLLPushBackNPZ(f, l, n, next, prev, CheckNull, SetNull)
#define DLLPushFront(f, l, n) DLLPushBackNPZ(l, f, n, prev, next, CheckNull, SetNull)
#define DLLInsert(f, l, p, n) DLLInsertNPZ(f, l, p, n, next, prev, CheckNull, SetNull)
#define DLLRemove(f, l, n)    DLLRemoveNPZ(f, l, n, next, prev, CheckNull, SetNull)

#endif// COMMON_DATA_STRUCTURE_H
