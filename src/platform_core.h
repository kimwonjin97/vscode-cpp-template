// FileName: platform_core.h
// Copyright (c) 2025 Wonjin Kim. All rights reserved.

#ifndef PLATFORM_CORE_H
#define PLATFORM_CORE_H

root_function u32 OS_PageSize();
root_function void * OS_Reserve(u64 Size);
root_function void OS_Release(void *Ptr, u64 Size);
root_function void OS_Commit(void *Ptr, u64 Size);
root_function void OS_Decommit(void* Ptr, u64 Size);


#endif //PLATFORM_CORE_H