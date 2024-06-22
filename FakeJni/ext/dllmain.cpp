#include <windows.h>
#include <include_header.h>

#include "jvm/context/JVMContext.hpp"
#include "jvm/fake/JavaVM.hpp"
#include "jvm/fake/JavaThread.hpp"
#include "titan_hook.h"
#include "veh/VEH.h"
#include "LOG.h"
#include <jvm/hotspot/jvm_internal.h>

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
typedef void (*reg_method)(JNIEnv*, jclass, jint, jclass);
TitanHook < reg_method> RegMethodHook;
reg_method orginal_reg_method;
FARPROC jni_onload = 0;
uintptr_t module_base = 0;



static void my_reg_method2(JNIEnv* env, jclass caller, jint id, jclass clazz) {
	LOG_P("my_reg_method2", "Enter");
	FakeJNI::current_context->env = env;

	auto restore_functions = env->functions;

	FakeJNI::before = [restore_functions](JNIEnv* fake) ->void {
		fake->functions = restore_functions;
		};

	env->functions = fake_native_interface;

	FakeJNI::after = [](JNIEnv* fake) -> void {
		fake->functions = fake_native_interface;
		};

	RegMethodHook.GetOrignalFunc()(env, caller, id, clazz);
}
static void my_reg_method(JNIEnv* env, jclass caller, jint id, jclass clazz) {
	LOG_P("my_reg_method", "Enter");
	LOG_FIELD_HEX(FakeJNI::current_context->jvmti.value());
	LOG_FIELD_HEX(clazz);
	char* sign{};
	FakeJNI::current_context->jvmti.value()->GetClassSignature(clazz, &sign, 0);
	std::string class_name(sign);
	std::cout << "Registering clazz_" << id << " : " << utils::misc::to_java_class_name(class_name) << std::endl;

	FakeJNI::current_context->env = env;

	auto restore_functions = env->functions;

	FakeJNI::before = [restore_functions](JNIEnv* fake) ->void {
		fake->functions = restore_functions;
		};

	env->functions = fake_native_interface;

	FakeJNI::after = [](JNIEnv* fake) -> void {
		fake->functions = fake_native_interface;
		};

	RegMethodHook.GetOrignalFunc()(env, caller, id, clazz);
	//orginal_reg_method(new FakeJNI::FakeJNIEnv(), caller, id, clazz);
}
jint my_jni_onload(JavaVM* vm, void*) {
	FakeJNI::current_context->vm = vm;
	JNIEnv* env{};
	std::cout << "Enter my_jni_onload And Force Return" << std::endl;
	vm->GetEnv((void**)&env, JNI_VERSION_1_6);
	orginal_reg_method = reinterpret_cast<reg_method>(module_base + 1440128);

	RegMethodHook.InitHook(reinterpret_cast<reg_method>(module_base + 1440128), my_reg_method);
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


	LoadLibraryAHook.InitHook(LoadLibraryA, my_loadlibrarya);
	LoadLibraryAHook.SetHook();
	FakeJNI::current_context->jvmti = jvmti_env;
	//InitJniHook(jni_env);
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

	//callbacks.NativeMethodBind = &NativeMethodBindHook;
	callbacks.VMInit = &VMInitHook;
	error = jvmti_env->SetEventCallbacks(&callbacks, sizeof(callbacks));
	if (error != JVMTI_ERROR_NONE) return error;
	return JNI_OK;
}

