#include <windows.h>
#include <include_header.h>

#include "jvm/context/JVMContext.hpp"
#include "jvm/fake/JavaVM.hpp"
#include "jvm/fake/JavaThread.hpp"
#include "titan_hook.h"
#include "veh/VEH.h"
#include "LOG.h"
#include <jvm/hotspot/jvm_internal.h>



template<class members_type>
std::map<members_type, std::string> class_name_cache;

namespace thread {
	inline size_t size = 0;
	inline void* address = 0;
	inline uint64_t offset_to_env = 0;
}

/* JVM exports some symbols that we need to use */
extern "C" JNIIMPORT VMStructEntry * gHotSpotVMStructs;
extern "C" JNIIMPORT VMTypeEntry * gHotSpotVMTypes;
extern "C" JNIIMPORT VMIntConstantEntry * gHotSpotVMIntConstants;
extern "C" JNIIMPORT VMLongConstantEntry * gHotSpotVMLongConstants;


FakeJNI::FakeJavaVM* fake_vm = new FakeJNI::FakeJavaVM();
FakeJNI::FakeNativeInterface* fake_native_interface = new FakeJNI::FakeNativeInterface();
FakeJNI::FakeJNIEnv* fake_env = new FakeJNI::FakeJNIEnv();


TitanHook<decltype(&LoadLibraryA)> LoadLibraryAHook;
typedef jint(JNICALL* JNI_OnLoad_t)(JavaVM*, void*);
FARPROC jni_onload = 0;
uintptr_t module_base = 0;


jint my_jni_onload(JavaVM* vm, void*) {
	FakeJNI::current_context->vm = vm;
	JNIEnv* env{};
	std::cout << "Enter my_jni_onload And Force Return" << std::endl;
	vm->GetEnv((void**)&env, JNI_VERSION_1_6);
	//RegMethodHook.SetHook();

	/* {
		LOG_FIELD_HEX(env);

		auto clazz = env->FindClass("antiLeak/Loader");

		LOG_FIELD_HEX(clazz);

		const JNINativeMethod nativeMethods_0[] = {
		{(char*)"registerNativesForClass" , (char*)"(ILjava/lang/Class;)V" , reinterpret_cast<void*>(&my_reg_method) }
		};
		env->RegisterNatives(clazz, nativeMethods_0, 1);

		LOG("Finished");
		return JNI_VERSION_1_2;
	}*/

	JavaVM_* jvm = new JavaVM_{
		(JNIInvokeInterface_*)fake_vm
	};

	return veh::CallOriginal<jint>(reinterpret_cast<JNI_OnLoad_t>(jni_onload), jvm, (void*)0);
}

static jint JNICALL showVerifyPanel(JNIEnv* env, jclass caller);
TitanHook<decltype(&showVerifyPanel)> HookShowVerifyPanel;
static jint JNICALL showVerifyPanel(JNIEnv* env, jclass caller) {

	FakeJNI::current_context->env = env;

	auto restore_functions = env->functions;

	FakeJNI::before = [restore_functions](JNIEnv* fake) ->void {
		fake->functions = restore_functions;
		};

	env->functions = fake_native_interface;

	FakeJNI::after = [](JNIEnv* fake) -> void {
		fake->functions = fake_native_interface;
		};
	return 1;
	return HookShowVerifyPanel.GetOrignalFunc()(env, caller);
}
static HMODULE my_loadlibrarya(LPCSTR module_path) {
	std::string path(module_path);
	auto result = LoadLibraryAHook.GetOrignalFunc()(module_path);
	if (path.find("Temp\\lib") != std::string::npos)
	{
		std::cout << "Lib :" << path << " Module :" << result << std::endl;
		module_base = reinterpret_cast<uintptr_t>(result);
		jni_onload = GetProcAddress(result, "JNI_OnLoad");
		veh::Setup();
		veh::Hook(jni_onload, my_jni_onload);
		std::cout << "JNI_OnLoad :" << jni_onload << std::endl;
	}
	return result;
}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
	}
	return TRUE;
}

static void JNICALL VMInitHook(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread) {
	JVMWrappers::init(gHotSpotVMStructs, gHotSpotVMTypes, gHotSpotVMIntConstants, gHotSpotVMLongConstants);

	auto type_thead = JVMWrappers::find_type("JavaThread").value();
	thread::size = type_thead->size;
	thread::address = VirtualAlloc(0, thread::size + 0x10, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	static VMStructEntry* _anchor_entry = JVMWrappers::find_type_fields("JavaThread").value().get()["_anchor"];
	static VMTypeEntry* _java_thread_type = JVMWrappers::find_type("JavaFrameAnchor").value();
	if (!_anchor_entry) {
		return;
	}

	thread::offset_to_env = _anchor_entry->offset + _java_thread_type->size + 8;
	LOG_FIELD(thread::size);
	LOG_FIELD(thread::address);
	LOG_FIELD(thread::offset_to_env);


	//LoadLibraryAHook.InitHook(LoadLibraryA, my_loadlibrarya);
	//LoadLibraryAHook.SetHook();
	FakeJNI::current_context->jvmti = jvmti_env;
	//InitJniHook(jni_env);
}

#include <handler/XinxinHandler.h>
static void JNICALL NativeMethodBindHook
(jvmtiEnv* jvmti_env, JNIEnv* jni_env, jthread thread,
	jmethodID methodid,
	void* address, void** new_address_ptr) {

	char* name;
	char* sign;
	jclass clazz;
	jvmti_env->GetMethodDeclaringClass(methodid, &clazz);
	char* clazzSign{};
	jvmti_env->GetClassSignature(clazz, &clazzSign, 0);
	jvmti_env->GetMethodName(methodid, &name, &sign, 0);
	//std::cout << "Going To Crash!!" << std::endl;
	if (!clazzSign)
	{
		return;
	}
	//std::cout << clazzSign << std::endl;
	auto clazzSignStr = std::string(clazzSign);
	if (clazzSignStr.find("Ljava/") != -1 || clazzSignStr.find("Lsun/") != -1 || clazzSignStr.find("Lcom/sun/jna/") != -1 || clazzSignStr.find("Lorg/lwjgl/") != -1)
	{
		return;
	}



	std::string signStr(sign);
	// std::cout << pMethod << " Name : " << pMethod->get_name() << std::endl;;
	std::string methodNameStr(name);

	std::cout << "Class::{ Name -> " << clazzSign << " NativeMethod::{ Name -> " << methodNameStr << "  Sign -> " << sign << " Addr-> " << address << "} }" << std::endl;

}
JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM* vm, char* options, void* reserved) {
	jvmtiEnv* jvmti_env;
	jvmtiError error;
	jint ret = vm->GetEnv((void**)&jvmti_env, JVMTI_VERSION);
	if (ret != JNI_OK) {
		return ret;
	}

	FakeJNI::current_context->jvmti = jvmti_env;


	jvmtiCapabilities capabilities;
	memset(&capabilities, 0, sizeof(capabilities));
	jvmti_env->GetCapabilities(&capabilities);
	capabilities.can_generate_native_method_bind_events = 1;
	jvmti_env->AddCapabilities(&capabilities);
	error = jvmti_env->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, NULL);
	if (error != JVMTI_ERROR_NONE) return error;


	error = jvmti_env->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_NATIVE_METHOD_BIND, NULL);
	if (error != JVMTI_ERROR_NONE) return error;

	jvmtiEventCallbacks callbacks;
	memset(&callbacks, 0, sizeof(callbacks));

	callbacks.NativeMethodBind = &NativeMethodBindHook;
	callbacks.VMInit = &VMInitHook;
	error = jvmti_env->SetEventCallbacks(&callbacks, sizeof(callbacks));
	if (error != JVMTI_ERROR_NONE) return error;
	return JNI_OK;
}

