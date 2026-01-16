// FileName: common_arena.h
// Copyright (c) 2025 Wonjin Kim. All rights reserved.

#ifndef COMMON_ARENA_H
#define COMMON_ARENA_H

struct arena 
{
	arena *Prev;
	arena *Current;

	u64 ReservedSize;
	u64 CommitedSize;

	u64 BasePos;
	u64 CurPos;

#if ARENA_FREE_LIST
	arena *FreeList;
#endif
};

struct temp_arena
{
	arena *Arena;
	u64    Pos;
};

global_variable u64 ARENA_DEFAULT_RESERVE_SIZE = Megabytes(64);
global_variable u64 ARENA_DEFAULT_COMMIT_SIZE  = Kilobytes(64);

root_function arena *ArenaAlloc(u64 ReservedSize = ARENA_DEFAULT_RESERVE_SIZE, u64 CommitedSize = ARENA_DEFAULT_COMMIT_SIZE);
root_function void   ArenaRelease(arena *Arena);

root_function void  *ArenaPush(arena* Arena, u64 Size, u64 Alignment);

root_function u64  ArenaPos(arena *Arena);
root_function void ArenaPopTo(arena *Arena, u64 Pos);

root_function void ArenaPop(arena *Arena, u64 Amt);
root_function void ArenaClear(arena *Arena);

root_function temp_arena TempBegin(arena *Arena);
root_function void      TempEnd(temp_arena Temp);

#define PushArrayNoZeroAligned(Arena, Type, Count, Align) (Type *)ArenaPush((Arena), sizeof(Type)*(Count), (Align))
#define PushArrayAligned(Arena, Type, Count, Align) (Type  *)MemoryZero(PushArrayNoZeroAligned(Arena, Type, Count, Align), sizeof(Type)*(Count))
#define PushArrayNoZero(Arena, Type, Count) PushArrayNoZeroAligned(Arena, Type, Count, Max(8, AlignOf(Type)))
#define PushArray(Arena, Type, Count) PushArrayAligned(Arena, Type, Count, Max(8, AlignOf(Type)))

#define PushStruct(Arena, Type, ...) (Type *)PushArrayAligned(Arena, Type, 1, Max(8, AlignOf(Type)))
#define PushSize(Arena, Size, ...) (Type *)PushArrayAligned(Arena, u8, Size, Max(8, AlignOf(Type)))

#endif// COMMON_ARENA_H
