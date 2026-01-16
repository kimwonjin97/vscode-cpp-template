// FileName: common_string.cpp
// Copyright (c) 2025 Wonjin Kim. All rights reserved.


root_function string8 String8(u8 *Str, u64 Size)
{
	string8 Result;

	Result.Str = Str;
	Result.Size = Size;

	return Result;
}

root_function string8 
PushStr8FV(arena *Arena, char *Fmt, va_list Args)
{
	string8 Result{};
	va_list Args2;
	va_copy(Args2, Args);
	u64 SizeInBytes = stbsp_vsnprintf(0, 0, Fmt, Args) + 1;
	Result.Str = PushArrayNoZero(Arena, u8, SizeInBytes);
	Result.Size = SizeInBytes - 1;
	stbsp_vsnprintf((char*)Result.Str, SizeInBytes, Fmt, Args2);
	return Result;
}


root_function string8
PushStr8F(arena *Arena, char *Fmt, ...)
{
	string8 Result{};
	va_list Args;
	va_start(Args, Fmt);
	Result = PushStr8FV(Arena, Fmt, Args);
	va_end(Args);

	return Result;
}
