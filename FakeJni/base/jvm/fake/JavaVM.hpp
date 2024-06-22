#pragma once

#include "include_header.h"
#include "../context/JVMContext.hpp"
#include  "JNIEnv.hpp"


#define _INVOKE_DEBUG(name) std::cout  << "DEBUG: JNIInvokeInterface_::" <<  #name << std::endl;;

BEGIN_FAKE_NAMESPACE

struct FakeJavaVM : public JNIInvokeInterface_
{
	FakeJavaVM() {
		DestroyJavaVM = [](JavaVM* vm) -> jint {
			_INVOKE_DEBUG(DestroyJavaVM)
				if (current_context->vm.has_value()) {
					return current_context->vm.value()->DestroyJavaVM();
				}
			return JNI_OK;
			};
		AttachCurrentThread = [](JavaVM* vm, void** penv, void* args) -> jint {
			_INVOKE_DEBUG(AttachCurrentThread)
				if (current_context->vm.has_value()) {
					return current_context->vm.value()->AttachCurrentThread(penv, args);
				}
			return JNI_OK;
			};
		DetachCurrentThread = [](JavaVM* vm) -> jint {
			_INVOKE_DEBUG(DetachCurrentThread)
				if (current_context->vm.has_value()) {
					return current_context->vm.value()->DetachCurrentThread();
				}
			return JNI_OK;
			};
		GetEnv = [](JavaVM* vm, void** penv, jint version) -> jint {
			_INVOKE_DEBUG(GetEnv)
				if (current_context->vm.has_value())
				{
					void* temp{};
					auto result = current_context->vm.value()->GetEnv(&temp, version);

					if (result != JNI_OK) return result;

					if (utils::misc::is_any_of(version, JNI_VERSION_1_1, JNI_VERSION_1_2, JNI_VERSION_1_4, JNI_VERSION_1_6, JNI_VERSION_1_8))
					{
						std::cout << "Getting JNIEnv" << std::endl;
						current_context->env = reinterpret_cast<JNIEnv*>(temp);
						*penv = new FakeJNIEnv();
					}
					else if (utils::misc::is_any_of(version, JVMTI_VERSION_1_0, JVMTI_VERSION_1_1, JVMTI_VERSION_1_2))
					{
						std::cout << "Getting jvmtiEnv" << std::endl;
						current_context->jvmti = reinterpret_cast<jvmtiEnv*>(temp);
						*penv = temp;
					}
				}
			return JNI_OK;
			};
		AttachCurrentThreadAsDaemon = [](::JavaVM* vm, void** penv, void* args) -> jint {
			_INVOKE_DEBUG(AttachCurrentThreadAsDaemon)
				if (current_context->vm.has_value()) {
					return current_context->vm.value()->AttachCurrentThreadAsDaemon(penv, args);
				}
			return JNI_OK;
			};
	}
};


END_FAKE_NAMESPACE
