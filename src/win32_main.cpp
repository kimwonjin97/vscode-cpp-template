// FileName: win32_main.cpp
// Copyright (c) 2025 Wonjin Kim. All rights reserved.

#include "common/common_includes.h"
#include "platform_core.h"
#include "win32_main.h"

#include "common/common_includes.cpp"

#define UNICODE 1
#include <windows.h>

/*
TODOs:
[x] 1. arena
2. scratch arena
2. basic datastructure example.
3. include stb library
4. basic renderer(d3d11)
5. start ui programming
6. Handmade hero 2개 듣고

*/

root_function u32
OS_PageSize()
{
	SYSTEM_INFO Info;
	GetSystemInfo(&Info);
	return Info.dwPageSize;
}

root_function void *
OS_Reserve(u64 Size)
{
	u64   GbSnappedSize = AlignUp(Size, Gigabytes(1));
	void *Ptr           = VirtualAlloc(0, GbSnappedSize, MEM_RESERVE, PAGE_NOACCESS);

	if (!Ptr)
	{
		BreakDebugger();
	}

	return Ptr;
}

root_function void
OS_Release(void *Ptr, u64 Size)
{
	VirtualFree(Ptr, 0, MEM_RELEASE);
}

root_function void
OS_Commit(void *Ptr, u64 Size)
{
	u64 PageSnappedSize = AlignUp(Size, OS_PageSize());
	VirtualAlloc(Ptr, PageSnappedSize, MEM_COMMIT, PAGE_READWRITE);
}

root_function void
OS_Decommit(void *Ptr, u64 Size)
{
	VirtualFree(Ptr, Size, MEM_DECOMMIT);
}

root_function LRESULT CALLBACK
Win32MainWindowCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	switch (uMsg)
	{
	case WM_DESTROY: {
		PostQuitMessage(0);
	}
	break;

	case WM_MOUSEMOVE: {
		OutputDebugString(L"Mouse moving");
	}
	break;

	default:
		Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return Result;
}

root_function void
DataStructureTest()
{

	struct foo
	{
		string8 Name;
		vec4 Color;
	};

	arena *Arena = ArenaAlloc();

	// Single Struct
	{
		foo *Foo  = PushStruct(Arena, foo);
		Foo->Name = String8Lit("Hello World");
		Foo->Color = vec4(1, 0, 0, 0);
		int x = 0;
	}


	// array of structs
	{
		u64 FooCount = 12;
		foo *Foos = PushArray(Arena, foo, FooCount);
		for(u64 Idx = 0; Idx < FooCount; ++Idx)
		{
			foo *Foo = &Foos[Idx];
			Foo->Name = PushStr8F(Arena, "Index: #%I64u", Idx);
			Foo->Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		int a = 10;
	}


	printf("%d", 35);



}

int WINAPI
WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, [[maybe_unused]] PSTR cmdline, [[maybe_unused]] int cmdshow)
{
	WNDCLASSEX window_class    = {};
	window_class.cbSize        = sizeof(window_class);
	window_class.style         = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc   = Win32MainWindowCallback;
	window_class.hInstance     = hInst;
	window_class.hCursor       = LoadCursor(0, IDC_ARROW);
	window_class.lpszClassName = L"project_template";

	if (RegisterClassEx(&window_class))
	{

		HWND WindowHandle = CreateWindowEx(
			0,
			window_class.lpszClassName,
			L"테스트",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			hInst,
			0);

		if (WindowHandle)
		{

			DataStructureTest();

			MSG Message;
			while (GetMessage(&Message, NULL, 0, 0))
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else
		{
			OutputDebugString(L"Failed to create window");
		}
	}
	else
	{
		OutputDebugString(L"Failed to register class");
	}
}
