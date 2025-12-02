#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <memory>

namespace Memory
{
inline static uintptr_t ToLocalAddress(const void* pPtr)
{
	return uintptr_t(pPtr) - uintptr_t(GetModuleHandle(NULL));
}

template <typename T>
inline static T& ReadRef(uintptr_t uOffset)
{
	return *reinterpret_cast<T*>(uintptr_t(GetModuleHandle(NULL)) + uOffset);
}

template <typename T>
inline static T* ReadPtr(uintptr_t uOffset)
{
	return reinterpret_cast<T*>(uintptr_t(GetModuleHandle(NULL)) + uOffset);
}

template <typename T>
inline static T Read(uintptr_t uOffset)
{
	return reinterpret_cast<T>(uintptr_t(GetModuleHandle(NULL)) + uOffset);
}

template <typename T>
void WriteGlobal(void* pAddr, const T& data)
{
	DWORD oldProtect;
	VirtualProtect(pAddr, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
	std::memcpy(pAddr, &data, sizeof(T));
	VirtualProtect(pAddr, sizeof(T), oldProtect, &oldProtect);
}

template <typename T>
void WriteMemory(uintptr_t uOffset, const T& data)
{
	//void* v_global_ptr = ReadPtr<void>(uOffset);
	WriteGlobal<T>(ReadPtr<void>(uOffset), data);
	//DWORD oldProtect;
	//VirtualProtect(v_global_ptr, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
	//std::memcpy(v_global_ptr, &data, sizeof(T));
	//VirtualProtect(v_global_ptr, sizeof(T), oldProtect, &oldProtect);
}

inline static void OverwriteVftable(void* pObj, uintptr_t uVtblOffset)
{
	*reinterpret_cast<void**>(pObj) = Memory::ReadPtr<void>(uVtblOffset);
}
}