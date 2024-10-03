#pragma once
#include "include_header.h"

BEGIN_FAKE_NAMESPACE

struct JVMContext
{
	std::optional<JNIEnv*>  env;
	std::optional<jvmtiEnv*>  jvmti;
	std::optional<JavaVM*>  vm;
	JNINativeInterface_* preserved_native_interface;
};

inline std::shared_ptr<JVMContext> current_context = std::make_shared<JVMContext>();

END_FAKE_NAMESPACE