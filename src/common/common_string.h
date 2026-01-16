// FileName: common_string.h
// Copyright (c) 2025 Wonjin Kim. All rights reserved.
#ifndef COMMON_STRING_H
#define COMMON_STRING_H

#define STB_SPRINTF_IMPLEMENTATION
#include "third_party/stb/stb_sprintf.h"


struct string8
{
	u8 *Str;
	u64 Size;
};

struct string16
{
	u16 *Str;
	u64 Size;
};


root_function string8 String8(u8 *Str, u64 Size);
#define String8Lit(s) String8((u8 *)s, sizeof(s) - 1)


root_function string8 PushStr8F(arena *Arena, char *Fmt, ...);

#endif //COMMON_STRING_H




