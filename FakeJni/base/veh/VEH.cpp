#include "veh.h"
#include "LOG.h"

void veh::Setup()
{
	GetSystemInfo(&system_info);
	handle = AddVectoredExceptionHandler(1, VectoredExceptionHandler);
}

bool veh::Hook(void* source, void* destination)
{
	if (!handle) {
		LOG_P("VehHooker", "Handle is empty.");
		return false;
	}

	MEMORY_BASIC_INFORMATION source_info;
	if (!VirtualQuery(source, &source_info, sizeof(MEMORY_BASIC_INFORMATION))) {
		LOG_P("VehHooker", "VirtualQuery failed[Stage 1].");
		return false;
	}

	MEMORY_BASIC_INFORMATION destination_info;
	if (!VirtualQuery(destination, &destination_info, sizeof(MEMORY_BASIC_INFORMATION))) {
		LOG_P("VehHooker", "VirtualQuery failed[Stage 2].");
		return false;
	}

	if (source_info.AllocationBase == destination_info.AllocationBase) {
		LOG_P("VehHooker", "Bro are you zero iq??");
		return false;
	}

	hooks.push_back({ source, destination });
	DWORD tmp;

	return VirtualProtect(source, 1, PAGE_EXECUTE_READ | PAGE_GUARD, &tmp);
}

void veh::Destroy()
{
	for (HookInfo_t& hook_info : hooks)
	{
		DWORD tmp;
		VirtualProtect(hook_info.source, 1, PAGE_EXECUTE_READ, &tmp);
	}

	hooks.clear();
	std::cout << "Hi Hanlde " << handle << std::endl;
	RemoveVectoredExceptionHandler(handle);
	handle = nullptr;
}

LONG veh::VectoredExceptionHandler(EXCEPTION_POINTERS* exception_info)
{
	if (exception_info->ExceptionRecord->ExceptionCode == EXCEPTION_GUARD_PAGE)
	{
		for (HookInfo_t& hook_info : hooks)
		{
			if (exception_info->ExceptionRecord->ExceptionAddress == hook_info.source)
			{
#ifdef _WIN64
				exception_info->ContextRecord->Rip = (DWORD64)hook_info.destination;
#else
				exception_info->ContextRecord->Eip = (DWORD)hook_info.destination;
#endif
			}
		}

		exception_info->ContextRecord->EFlags |= PAGE_GUARD;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if (exception_info->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	{
		for (HookInfo_t& hook_info : hooks)
		{
			DWORD tmp{};
			VirtualProtect(hook_info.source, 1, PAGE_EXECUTE_READ, &tmp);
		}
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}