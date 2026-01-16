// FileName: common_core.h
// Copyright (c) 2025 Wonjin Kim. All rights reserved.

#ifndef COMMON_CORE_H
#define COMMON_CORE_H

// NOTE(wj): ThirdParties
#include <cstddef>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#if COMPILER_MSVC
#include <intrin.h>
#endif

// NOTE(Wj): Platform Definitions

#if defined(_MSC_VER)

	#define COMPILER_MSVC 1

	#if defined(_WIN32)
		#define OS_WINDOWS 1
	#else
		#error _MSC_VER is defined, but _WIN32 is not. This setup is not supported.
	#endif

	#if defined(_M_AMD64)
		#define ARCH_X64 1
	#elif defined(_M_IX86)
		#define ARCH_X86 1
	#elif defined(_M_ARM64)
		#define ARCH_ARM64 1
	#elif defined(_M_ARM)
		#define ARCH_ARM32 1
	#else
		#error Target architecture is not supported. _MSC_VER is defined, but one of {_M_AMD64, _M_IX86, _M_ARM64, _M_ARM} is not.
	#endif

	#if _MSC_VER >= 1920
		#define COMPILER_MSVC_YEAR 2019
	#elif _MSC_VER >= 1910
		#define COMPILER_MSVC_YEAR 2017
	#elif _MSC_VER >= 1900
		#define COMPILER_MSVC_YEAR 2015
	#elif _MSC_VER >= 1800
		#define COMPILER_MSVC_YEAR 2013
	#elif _MSC_VER >= 1700
		#define COMPILER_MSVC_YEAR 2012
	#elif _MSC_VER >= 1600
		#define COMPILER_MSVC_YEAR 2010
	#elif _MSC_VER >= 1500
		#define COMPILER_MSVC_YEAR 2008
	#elif _MSC_VER >= 1400
		#define COMPILER_MSVC_YEAR 2005
	#else
		#define COMPILER_MSVC_YEAR 0
	#endif

#elif defined(__clang__)

	#define COMPILER_CLANG 1

	#if defined(__APPLE__) && defined(__MACH__)
		#define OS_MAC 1
	#elif defined(__gnu_linux__)
		#define OS_LINUX 1
	#else
		#error __clang__ is defined, but one of {__APPLE__, __gnu_linux__} is not. This setup is not supported.
	#endif

	#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
		#define ARCH_X64 1
	#elif defined(i386) || defined(__i386) || defined(__i386__)
		#define ARCH_X86 1
	#elif defined(__aarch64__)
		#define ARCH_ARM64 1
	#elif defined(__arm__)
		#define ARCH_ARM32 1
	#else
		#error Target architecture is not supported. __clang__ is defined, but one of {__amd64__, __amd64, __x86_64__, __x86_64, i386, __i386, __i386__, __aarch64__, __arm__} is not.
	#endif

#elif defined(__GNUC__) || defined(__GNUG__)

	#define COMPILER_GCC 1

	#if defined(__gnu_linux__)
		#define OS_LINUX 1
	#else
		#error __GNUC__ or __GNUG__ is defined, but __gnu_linux__ is not. This setup is not supported.
	#endif

	#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
		#define ARCH_X64 1
	#elif defined(i386) || defined(__i386) || defined(__i386__)
		#define ARCH_X86 1
	#elif defined(__aarch64__)
		#define ARCH_ARM64 1
	#elif defined(__arm__)
		#define ARCH_ARM32 1
	#else
		#error Target architecture is not supported. __GNU_C__ or __GNUG__ is defined, but one of {__amd64__, __amd64, __x86_64__, __x86_64, i386, __i386, __i386__, __aarch64__, __arm__} is not.
	#endif

#else
	#error Compiler is not supported. _MSC_VER, __clang__, __GNUC__, or __GNUG__ must be defined.
#endif

#if defined(ARCH_X64)
	#define ARCH_64BIT 1
#elif defined(ARCH_X86)
	#define ARCH_32BIT 1

#endif

#if defined(__cplusplus)
	#define LANG_CPP 1
#else
	#define LANG_C 1
#endif

#if !defined(ARCH_32BIT)
	#define ARCH_32BIT 0
#endif
#if !defined(ARCH_64BIT)
	#define ARCH_64BIT 0
#endif
#if !defined(ARCH_X64)
	#define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
	#define ARCH_X86 0
#endif
#if !defined(ARCH_ARM64)
	#define ARCH_ARM64 0
#endif
#if !defined(ARCH_ARM32)
	#define ARCH_ARM32 0
#endif
#if !defined(COMPILER_MSVC)
	#define COMPILER_MSVC 0
#endif
#if !defined(COMPILER_GCC)
	#define COMPILER_GCC 0
#endif
#if !defined(COMPILER_CLANG)
	#define COMPILER_CLANG 0
#endif
#if !defined(OS_WINDOWS)
	#define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
	#define OS_LINUX 0
#endif
#if !defined(OS_MAC)
	#define OS_MAC 0
#endif
#if !defined(LANG_CPP)
	#define LANG_CPP 0
#endif
#if !defined(LANG_C)
	#define LANG_C 0
#endif

// Note(Wj): Types

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  b8;
typedef int16_t b16;
typedef int32_t b32;
typedef int64_t b64;

typedef float  f32;
typedef double f64;

// NOTE(Wj): KeyWords

#define internal        static
#define function        static
#define local_persist   static
#define global_variable static
#define static_member   static

#if LANG_CPP
	#define no_name_mangle extern "C"
#else
	#define no_name_mangle
#endif

#define root_global   no_name_mangle
#define root_function no_name_mangle function

#if OS_WINDOWS
	#define exported no_name_mangle __declspec(dllexport)
#else
	#define exported no_name_mangle
#endif

#if OS_WINDOWS
	#define imported no_name_mangle __declspec(dllimport)
#else
	#define imported no_name_mangle
#endif

#if COMPILER_MSVC && COMPILER_MSVC_YEAR < 2015
	#define inline_function static
#else
	#define inline_function inline static
#endif

#if COMPILER_MSVC && COMPILER_MSVC_YEAR < 2015
	#define this_function_name "unknown"
#else
	#define this_function_name __func__
#endif

#if COMPILER_MSVC || (COMPILER_CLANG && PLATFORM_WINDOWS)
	#pragma section(".rdata$", read)
	#define read_only __declspec(allocate(".rdata$"))
#elif (COMPILER_CLANG && !PLATFORM_WINDOWS)
	#define read_only __attribute__((section(".rodata")))
#else
	#define read_only
#endif

#if LANG_CPP
	#define zero_struct \
		{               \
		}
#else
	#define zero_struct { 0 }
#endif

#if PLATFORM_WINDOWS
	#define BreakDebugger() __debugbreak()
#else
	#define BreakDebugger() (*(volatile int *)0 = 0)
#endif

#define AssertAlways(b)      \
	do                       \
	{                        \
		if (!(b))            \
		{                    \
			BreakDebugger(); \
		}                    \
	}                        \
	while (0)

#if _DEBUG
	#define Assert(Expression)        \
		do                            \
		{                             \
			if (!(Expression))        \
			{                         \
				BreakDebugger(); \
			}                         \
		}                             \
		while (0)
#else
	#define Assert(Expression) ((void)(b))
#endif

#define NotImplemented AssertAlways(!"Not Implemented")
#define InvalidPath    AssertAlways(!"Invalid Path")

#if OS_WINDOWS
	#define AtomicIncEval64(ptr)                       InterlockedIncrement64((volatile long long *)(ptr))
	#define AtomicDecEval64(ptr)                       InterlockedDecrement64((volatile long long *)(ptr))
	#define AtomicAddEval64(ptr, val)                  InterlockedAdd64((volatile long long *)(ptr), (val))
	#define AtomicEvalSet64(ptr, val)                  InterlockedExchange64((volatile long long *)(ptr), (val))
	#define AtomicEval64(ptr)                          InterlockedAdd64((volatile long long *)(ptr), 0)
	#define AtomicEvalCompareExchange64(ptr, val, cmp) InterlockedCompareExchange64((volatile long long *)(ptr), (val), (cmp))
#else
	#error Atomics not implemented for this build configuration.
#endif

#if COMPILER_MSVC
	#define AlignOf(T) __alignof(T)
#elif COMPILER_CLANG
	#define AlignOf(T) __alignof(T)
#elif COMPILER_GCC
	#define AlignOf(T) __alignof__(T)
#else
	#error AlignOf not defined for this compiler.
#endif

// NOTE(wj): macros

#define HasBit(n, pos) (n & (1 << (pos)))

#define FlagSet(n, f)    ((n) |= (f))
#define FlagClear(n, f)  ((n) &= ~(f))
#define FlagToggle(n, f) ((n) ^= (f))
#define FlagExists(n, f) ((n) & (f))
#define FlagEquals(n, f) ((n) == (f))

// Checks if any bitrs in 'f' are set in 'n'
#define FlagIntersets(n, f) (((n) & (f)) > 0)

#define IsBetween(x, lower, upper) (((lower) <= (x)) && ((x) <= (upper)))

#define Bytes(n)     (n)
#define Kilobytes(n) (n << 10)
#define Megabytes(n) (n << 20)
#define Gigabytes(n) (((u64)n) << 30)
#define Terabytes(n) (((u64)n) << 40)

#define Thousand(n) ((n) * 1000)
#define Million(n)  ((n) * 1000000)
#define Billion(n)  ((n) * 1000000000LL)

#define ArrayCount(a)                          (sizeof(a) / sizeof((a)[0]))
#define IntFromPtr(p)                          (U64)(((U8 *)p) - 0)
#define PtrFromInt(i)                          (void *)(((U8 *)0) + i)
#define AlignPow2(x, b)                        (((x) + (b) - 1) & (~((b) - 1)))
#define AlignDownPow2(x, b)                    ((x) & (~((b) - 1)))
#define Member(type, member_name)              ((type *)0)->member_name
#define OffsetOf(type, member_name)            IntFromPtr(&Member(type, member_name))
#define BaseFromMember(type, member_name, ptr) (type *)((U8 *)(ptr) - OffsetOf(type, member_name))
#define AbsoluteValueS16(x)                    (S16) abs((x))
#define AbsoluteValueS32(x)                    (S32) abs((x))
#define AbsoluteValueS64(x)                    (S64) llabs((S64)(x))
#define AbsoluteValueU64(x)                    (U64) llabs((U64)(x))

#define AlignUp(value, alignment)     ((((u64)(value) + ((u64)(alignment) - 1)) / (u64)(alignment)) * (u64)(alignment))
#define AlignUpPow2(value, alignment) (((u64)(value) + ((u64)(alignment) - 1)) & ~((u64)(alignment) - 1))

#define Swap(type, a, b)            \
	do                              \
	{                               \
		type _swapper_ = a;         \
		a              = b;         \
		b              = _swapper_; \
	}                               \
	while (0)

#define MemoryCopy(dst, src, size) memcpy((dst), (src), (size))
#define MemoryMove(dst, src, size) memmove((dst), (src), (size))
#define MemorySet(dst, byte, size) memset((dst), (byte), (size))

#define MemoryCopyStruct(dst, src)                \
	do                                            \
	{                                             \
		Assert(sizeof(*(dst)) == sizeof(*(src))); \
		MemoryCopy((dst), (src), sizeof(*(dst))); \
	}                                             \
	while (0)
#define MemoryCopyArray(dst, src)              \
	do                                         \
	{                                          \
		Assert(sizeof(dst) == sizeof(src));    \
		MemoryCopy((dst), (src), sizeof(src)); \
	}                                          \
	while (0)

#define MemoryZero(ptr, size) MemorySet((ptr), 0, (size))
#define MemoryZeroStruct(ptr) MemoryZero((ptr), sizeof(*(ptr)))
#define MemoryZeroArray(arr)  MemoryZero((arr), sizeof(arr))

#define Min(a, b)      (((a) < (b)) ? (a) : (b))
#define Max(a, b)      (((a) > (b)) ? (a) : (b))
#define ClampTop(x, a) Min(x, a)
#define ClampBot(a, x) Max(a, x)
#define Clamp(a, x, b) (((a) > (x)) ? (a) : ((b) < (x)) ? (b)  \
														: (x))

#endif COMMON_CORE_H
