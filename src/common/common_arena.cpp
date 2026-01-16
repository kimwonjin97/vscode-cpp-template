// FileName: common_arena.cpp
// Copyright (c) 2025 Wonjin Kim. All rights reserved.

root_function arena *
ArenaAlloc(u64 ReservedSize, u64 CommitedSize)
{
	// TODO(Wj): reservedSize and CommitedSize are all aligned by default.
	// Check if we need to store the original requested reserved and commited size.
	ReservedSize = AlignUpPow2(ReservedSize, OS_PageSize());
	CommitedSize = AlignUpPow2(CommitedSize, OS_PageSize());

	void *Base = OS_Reserve(ReservedSize);
	OS_Commit(Base, CommitedSize);

	arena *Arena       = (arena *)Base;
	Arena->Current      = Arena;
	Arena->ReservedSize = ReservedSize;
	Arena->CommitedSize = CommitedSize;
	Arena->BasePos      = 0;
	Arena->CurPos       = sizeof(arena);

	return Arena;
}

root_function void
ArenaRelease(arena *Arena)
{
	for (arena *Next = Arena->Current, *Prev = 0; Next != 0; Next = Prev)
	{
		Prev = Next->Prev;
		OS_Release(Next, Next->ReservedSize);
	}
}

root_function arena *
ArenaAllocChainedblock_(arena *Current, u64 ReserveSize, u64 CommitSize, u64 Alignment, u64 RequestedSize)
{
	// Note(Wj): Adjust sizes if the requested allocation won't fit
	if (RequestedSize + sizeof(arena) > ReserveSize)
	{
		ReserveSize = AlignUpPow2(RequestedSize + sizeof(arena), Alignment);
		CommitSize  = AlignUpPow2(RequestedSize + sizeof(arena), Alignment);
	}

	arena *NewBlock   = ArenaAlloc(ReserveSize, CommitSize);
	NewBlock->BasePos = Current->BasePos + Current->ReservedSize;
	StackPushN(Current, NewBlock, Prev);

	return NewBlock;
}

root_function void *
ArenaPush(arena *Arena, u64 Size, u64 Alignment)
{
	arena *Current = Arena->Current;
	u64    PrePos  = AlignUpPow2(Arena->CurPos, Alignment);
	u64    PostPos = PrePos + Size;

	// Note(wj): Chain new arena block if needed
	if (PostPos > Arena->ReservedSize)
	{
		u64 ReserveSize = Arena->ReservedSize;
		u64 CommitSize  = Arena->CommitedSize;

		Current = ArenaAllocChainedblock_(Current, ReserveSize, CommitSize, Alignment, Size);
		PrePos  = AlignUpPow2(Current->CurPos, Alignment);
		PostPos = PrePos + Size;
	}

	// Note(wj): Commit more pages if needed
	if (PostPos > Current->CommitedSize)
	{
		u64 CommitTop    = ClampTop(AlignUpPow2(PostPos, Current->CommitedSize), Current->ReservedSize);
		u64 CommitAmount = CommitTop - Current->CommitedSize;

		u8 *CommitPtr = (u8 *)Current + Current->CommitedSize;
		OS_Commit(CommitPtr, CommitAmount);

		Current->CommitedSize += CommitAmount;
	}

	void *Result = nullptr;
	if (Current->CommitedSize >= PostPos)
	{
		Result          = (u8 *)Current + PrePos;
		Current->CurPos = PostPos;
	}

	return Result;
}

root_function u64
ArenaPos(arena *Arena)
{
	arena *Current = Arena->Current;
	u64    Pos     = Current->BasePos + Current->CurPos;
	return Pos;
}

root_function void
ArenaPopTo(arena *Arena, u64 Pos)
{
	u64    ClampedPos = ClampBot(sizeof(arena), Pos);
	arena *Cur        = Arena->Current;

	while (Cur && (Cur->BasePos >= ClampedPos))
	{
		arena *Prev = Cur->Prev;
		OS_Release(Cur, Cur->ReservedSize);
		Cur = Prev;
	}

	// Update arena state
	Arena->Current = Cur;

	if (Cur)
	{
		u64 NewPos = ClampedPos - Cur->BasePos;
		Assert(NewPos <= Cur->CurPos);
		Cur->CurPos = NewPos;
	}
}

root_function void
ArenaPop(arena *Arena, u64 Amt)
{
	u64 PosOld = ArenaPos(Arena);
	u64 PosNew = PosOld;

	if (Amt < PosOld)
	{
		PosNew = PosOld - Amt;
	}

	ArenaPopTo(Arena, PosNew);
}

root_function void
ArenaClear(arena *Arena)
{
	ArenaPopTo(Arena, 0);
}

root_function temp_arena 
TempBegin(arena *Arena)
{
	u64       Pos  = ArenaPos(Arena);
	temp_arena Temp = { Arena, Pos };
	return Temp;
}

root_function void
TempEnd(temp_arena temp)
{
	ArenaPopTo(temp.Arena, temp.Pos);
}
