#pragma once
#include <Windows.h>
#include <vector>
struct HookInfo_t
{
    void* source;
    void* destination;
};

namespace veh
{
    void Setup();
    bool Hook(void* source, void* destination);
    void Destroy();
    LONG VectoredExceptionHandler(EXCEPTION_POINTERS* exception_info);

    template <typename ReturnType, typename Prototype, typename... Args>
    ReturnType CallOriginal(Prototype source, Args... args);

    inline SYSTEM_INFO system_info;
    inline PVOID handle;
    inline std::vector<HookInfo_t> hooks;
}

template <typename ReturnType, typename Prototype, typename... Args>
ReturnType veh::CallOriginal(Prototype source, Args... args)
{
    DWORD old_protection;

    if constexpr (std::is_void_v<ReturnType>)
    {
        VirtualProtect(source, 1, PAGE_EXECUTE_READ, &old_protection);
        source(args...);
    }
    else
    {
        VirtualProtect(source, 1, PAGE_EXECUTE_READ, &old_protection);
        ReturnType result = source(args...);
        return result;
    }
}