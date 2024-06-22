#pragma once
#include "include_header.h"


#include "jvm/context/JVMContext.hpp"
#include <Windows.h>
#include <LOG.h>
#define OUTPUT
#define current_env current_context->env.value()
#ifdef OUTPUT
#define _INVOKE_DEBUG(name) log << "DEBUG: JNINativeInterface_::" <<  #name << std::endl
#else // OUTPUT
#define _INVOKE_DEBUG(name)
#endif



BEGIN_FAKE_NAMESPACE

inline std::ofstream log("log.txt", std::ios::app);

inline std::function<void(JNIEnv*)> before = [](JNIEnv*) {
	};
inline std::function<void(JNIEnv*)> after = [](JNIEnv*) {
	};

struct FakeNativeInterface : public JNINativeInterface_ {
	FakeNativeInterface() {

		GetVersion = [](JNIEnv* env) -> jint {
			_INVOKE_DEBUG(GetVersion);
			before(env);
			auto result = current_env->GetVersion();
			after(env);
			return result;
			};

		FindClass = [](JNIEnv* env, const char* name) -> jclass {
#ifdef OUTPUT
			log << "DEBUG: JNINativeInterface_::FindClass :" << name << std::endl;
#endif // OUTPUT
			before(env);
			auto result = current_env->FindClass(name);
			after(env);
			return result;
			};

		DefineClass = [](JNIEnv* env, const char* name, jobject loader, const jbyte* buf,
			jsize len) -> jclass {
				_INVOKE_DEBUG(GetVersion);
				before(env);
				auto result = current_env->DefineClass(name, loader, buf, len);
				after(env);
				return result;
			};

		FromReflectedMethod = [](JNIEnv* env, jobject method) -> jmethodID {
			_INVOKE_DEBUG(FromReflectedMethod);
			before(env);
			auto result = current_env->FromReflectedMethod(method);
			after(env);
			return result;
			};

		FromReflectedField = [](JNIEnv* env, jobject field) -> jfieldID {
			_INVOKE_DEBUG(FromReflectedField);
			before(env);
			auto result = current_env->FromReflectedField(field);
			after(env);
			return result;
			};

		ToReflectedMethod = [](JNIEnv* env, jclass cls, jmethodID methodID, jboolean isStatic) -> jobject {
			_INVOKE_DEBUG(ToReflectedMethod);
			before(env);
			auto result = current_env->ToReflectedMethod(cls, methodID, isStatic);
			after(env);
			return result;
			};

		GetSuperclass = [](JNIEnv* env, jclass sub) -> jclass {
			_INVOKE_DEBUG(GetSuperclass);
			before(env);
			auto result = current_env->GetSuperclass(sub);
			after(env);
			return result;
			};

		IsAssignableFrom = [](JNIEnv* env, jclass sub, jclass sup) -> jboolean {
			_INVOKE_DEBUG(IsAssignableFrom);
			before(env);
			auto result = current_env->IsAssignableFrom(sub, sup);
			after(env);
			return result;
			};

		ToReflectedField = [](JNIEnv* env, jclass cls, jfieldID fieldID, jboolean isStatic) -> jobject {
			_INVOKE_DEBUG(ToReflectedField);
			before(env);
			auto result = current_env->ToReflectedField(cls, fieldID, isStatic);
			after(env);
			return result;
			};

		Throw = [](JNIEnv* env, jthrowable obj) -> jint {
			_INVOKE_DEBUG(Throw);
			before(env);
			auto result = current_env->Throw(obj);
			after(env);
			return result;
			};

		ThrowNew = [](JNIEnv* env, jclass clazz, const char* msg) -> jint {
			_INVOKE_DEBUG(ThrowNew);
			before(env);
			auto result = current_env->ThrowNew(clazz, msg);
			after(env);
			return result;
			};

		ExceptionOccurred = [](JNIEnv* env) -> jthrowable {
			_INVOKE_DEBUG(ExceptionOccurred);
			before(env);
			auto result = current_env->ExceptionOccurred();
			after(env);
			return result;
			};

		ExceptionDescribe = [](JNIEnv* env) {
			_INVOKE_DEBUG(ExceptionDescribe);
			before(env);
			current_env->ExceptionDescribe();
			after(env);
			};

		ExceptionClear = [](JNIEnv* env) {
			_INVOKE_DEBUG(ExceptionClear);
			before(env);
			current_env->ExceptionClear();
			after(env);
			};

		FatalError = [](JNIEnv* env, const char* msg) {
			_INVOKE_DEBUG(FatalError);
			before(env);
			current_env->FatalError(msg);
			after(env);
			};

		PushLocalFrame = [](JNIEnv* env, jint capacity) -> jint {
			_INVOKE_DEBUG(PushLocalFrame);
			before(env);
			auto result = current_env->PushLocalFrame(capacity);
			after(env);
			return result;
			};

		PopLocalFrame = [](JNIEnv* env, jobject result) -> jobject {
			_INVOKE_DEBUG(PopLocalFrame);
			before(env);
			auto ret = current_env->PopLocalFrame(result);
			after(env);
			return ret;
			};

		NewGlobalRef = [](JNIEnv* env, jobject lobj) -> jobject {
			_INVOKE_DEBUG(NewGlobalRef);
			before(env);
			auto result = current_env->NewGlobalRef(lobj);
			after(env);
			return result;
			};

		DeleteGlobalRef = [](JNIEnv* env, jobject gref) {
			_INVOKE_DEBUG(DeleteGlobalRef);
			before(env);
			current_env->DeleteGlobalRef(gref);
			after(env);
			};

		DeleteLocalRef = [](JNIEnv* env, jobject obj) {
			_INVOKE_DEBUG(DeleteLocalRef);
			before(env);
			current_env->DeleteLocalRef(obj);
			after(env);
			};

		IsSameObject = [](JNIEnv* env, jobject obj1, jobject obj2) -> jboolean {
			_INVOKE_DEBUG(IsSameObject);
			before(env);
			auto result = current_env->IsSameObject(obj1, obj2);
			after(env);
			return result;
			};

		NewLocalRef = [](JNIEnv* env, jobject ref) -> jobject {
			_INVOKE_DEBUG(NewLocalRef);
			before(env);
			auto result = current_env->NewLocalRef(ref);
			after(env);
			return result;
			};

		EnsureLocalCapacity = [](JNIEnv* env, jint capacity) -> jint {
			_INVOKE_DEBUG(EnsureLocalCapacity);
			before(env);
			auto result = current_env->EnsureLocalCapacity(capacity);
			after(env);
			return result;
			};

		AllocObject = [](JNIEnv* env, jclass clazz) -> jobject {
			_INVOKE_DEBUG(AllocObject);
			before(env);
			auto result = current_env->AllocObject(clazz);
			after(env);
			return result;
			};

		NewObject = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jobject {
			_INVOKE_DEBUG(NewObject);
			before(env);
			va_list args;
			va_start(args, methodID);
			jobject result = current_env->NewObjectV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		NewObjectV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jobject {
			_INVOKE_DEBUG(NewObjectV);
			before(env);
			auto result = current_env->NewObjectV(clazz, methodID, args);
			after(env);
			return result;
			};

		NewObjectA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jobject {
			_INVOKE_DEBUG(NewObjectA);
			before(env);
			auto result = current_env->NewObjectA(clazz, methodID, args);
			after(env);
			return result;
			};

		GetObjectClass = [](JNIEnv* env, jobject obj) -> jclass {
			_INVOKE_DEBUG(GetObjectClass);
			before(env);
			auto result = current_env->GetObjectClass(obj);
			after(env);
			return result;
			};

		IsInstanceOf = [](JNIEnv* env, jobject obj, jclass clazz) -> jboolean {
			_INVOKE_DEBUG(IsInstanceOf);
			before(env);
			auto result = current_env->IsInstanceOf(obj, clazz);
			after(env);
			return result;
			};

		GetMethodID = [](JNIEnv* env, jclass clazz, const char* name, const char* sig) -> jmethodID {
			_INVOKE_DEBUG(GetMethodID);
			before(env);
			auto result = current_env->GetMethodID(clazz, name, sig);
			after(env);
			return result;
			};

		CallObjectMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jobject {
			_INVOKE_DEBUG(CallObjectMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jobject result = current_env->CallObjectMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallObjectMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jobject {
			_INVOKE_DEBUG(CallObjectMethodV);
			before(env);
			auto result = current_env->CallObjectMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallObjectMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jobject {
			_INVOKE_DEBUG(CallObjectMethodA);
			before(env);
			auto result = current_env->CallObjectMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallBooleanMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jboolean {
			_INVOKE_DEBUG(CallBooleanMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jboolean result = current_env->CallBooleanMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallBooleanMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jboolean {
			_INVOKE_DEBUG(CallBooleanMethodV);
			before(env);
			auto result = current_env->CallBooleanMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallBooleanMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jboolean {
			_INVOKE_DEBUG(CallBooleanMethodA);
			before(env);
			auto result = current_env->CallBooleanMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallByteMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jbyte {
			_INVOKE_DEBUG(CallByteMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jbyte result = current_env->CallByteMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallByteMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jbyte {
			_INVOKE_DEBUG(CallByteMethodV);
			before(env);
			auto result = current_env->CallByteMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallByteMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jbyte {
			_INVOKE_DEBUG(CallByteMethodA);
			before(env);
			auto result = current_env->CallByteMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallCharMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jchar {
			_INVOKE_DEBUG(CallCharMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jchar result = current_env->CallCharMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallCharMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jchar {
			_INVOKE_DEBUG(CallCharMethodV);
			before(env);
			auto result = current_env->CallCharMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallCharMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jchar {
			_INVOKE_DEBUG(CallCharMethodA);
			before(env);
			auto result = current_env->CallCharMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallShortMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jshort {
			_INVOKE_DEBUG(CallShortMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jshort result = current_env->CallShortMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallShortMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jshort {
			_INVOKE_DEBUG(CallShortMethodV);
			before(env);
			auto result = current_env->CallShortMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallShortMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jshort {
			_INVOKE_DEBUG(CallShortMethodA);
			before(env);
			auto result = current_env->CallShortMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallIntMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jint {
			_INVOKE_DEBUG(CallIntMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jint result = current_env->CallIntMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallIntMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jint {
			_INVOKE_DEBUG(CallIntMethodV);
			before(env);
			auto result = current_env->CallIntMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallIntMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jint {
			_INVOKE_DEBUG(CallIntMethodA);
			before(env);
			auto result = current_env->CallIntMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallLongMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jlong {
			_INVOKE_DEBUG(CallLongMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jlong result = current_env->CallLongMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallLongMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jlong {
			_INVOKE_DEBUG(CallLongMethodV);
			before(env);
			auto result = current_env->CallLongMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallLongMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jlong {
			_INVOKE_DEBUG(CallLongMethodA);
			before(env);
			auto result = current_env->CallLongMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallFloatMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jfloat {
			_INVOKE_DEBUG(CallFloatMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jfloat result = current_env->CallFloatMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallFloatMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jfloat {
			_INVOKE_DEBUG(CallFloatMethodV);
			before(env);
			auto result = current_env->CallFloatMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallFloatMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jfloat {
			_INVOKE_DEBUG(CallFloatMethodA);
			before(env);
			auto result = current_env->CallFloatMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallDoubleMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) -> jdouble {
			_INVOKE_DEBUG(CallDoubleMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jdouble result = current_env->CallDoubleMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			return result;
			};


		CallDoubleMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) -> jdouble {
			_INVOKE_DEBUG(CallDoubleMethodV);
			before(env);
			auto result = current_env->CallDoubleMethodV(obj, methodID, args);
			after(env);
			return result;
			};

		CallDoubleMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) -> jdouble {
			_INVOKE_DEBUG(CallDoubleMethodA);
			before(env);
			auto result = current_env->CallDoubleMethodA(obj, methodID, args);
			after(env);
			return result;
			};

		CallVoidMethod = [](JNIEnv* env, jobject obj, jmethodID methodID, ...) {
			_INVOKE_DEBUG(CallVoidMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			current_env->CallVoidMethodV(obj, methodID, args);
			va_end(args);
			after(env);
			};

		CallVoidMethodV = [](JNIEnv* env, jobject obj, jmethodID methodID, va_list args) {
			_INVOKE_DEBUG(CallVoidMethodV);
			before(env);
			current_env->CallVoidMethodV(obj, methodID, args);
			after(env);
			};

		CallVoidMethodA = [](JNIEnv* env, jobject obj, jmethodID methodID, const jvalue* args) {
			_INVOKE_DEBUG(CallVoidMethodA);
			before(env);
			current_env->CallVoidMethodA(obj, methodID, args);
			after(env);
			};

		CallNonvirtualObjectMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jobject {
			_INVOKE_DEBUG(CallNonvirtualObjectMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jobject result = current_env->CallNonvirtualObjectMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualObjectMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jobject {
			_INVOKE_DEBUG(CallNonvirtualObjectMethodV);
			before(env);
			auto result = current_env->CallNonvirtualObjectMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualObjectMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jobject {
			_INVOKE_DEBUG(CallNonvirtualObjectMethodA);
			before(env);
			auto result = current_env->CallNonvirtualObjectMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualBooleanMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jboolean {
			_INVOKE_DEBUG(CallNonvirtualBooleanMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jboolean result = current_env->CallNonvirtualBooleanMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualBooleanMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jboolean {
			_INVOKE_DEBUG(CallNonvirtualBooleanMethodV);
			before(env);
			auto result = current_env->CallNonvirtualBooleanMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualBooleanMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jboolean {
			_INVOKE_DEBUG(CallNonvirtualBooleanMethodA);
			before(env);
			auto result = current_env->CallNonvirtualBooleanMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualByteMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jbyte {
			_INVOKE_DEBUG(CallNonvirtualByteMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jbyte result = current_env->CallNonvirtualByteMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualByteMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jbyte {
			_INVOKE_DEBUG(CallNonvirtualByteMethodV);
			before(env);
			auto result = current_env->CallNonvirtualByteMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualByteMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jbyte {
			_INVOKE_DEBUG(CallNonvirtualByteMethodA);
			before(env);
			auto result = current_env->CallNonvirtualByteMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualCharMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jchar {
			_INVOKE_DEBUG(CallNonvirtualCharMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jchar result = current_env->CallNonvirtualCharMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualCharMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jchar {
			_INVOKE_DEBUG(CallNonvirtualCharMethodV);
			before(env);
			auto result = current_env->CallNonvirtualCharMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualCharMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jchar {
			_INVOKE_DEBUG(CallNonvirtualCharMethodA);
			before(env);
			auto result = current_env->CallNonvirtualCharMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualShortMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jshort {
			_INVOKE_DEBUG(CallNonvirtualShortMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jshort result = current_env->CallNonvirtualShortMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualShortMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jshort {
			_INVOKE_DEBUG(CallNonvirtualShortMethodV);
			before(env);
			auto result = current_env->CallNonvirtualShortMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualShortMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jshort {
			_INVOKE_DEBUG(CallNonvirtualShortMethodA);
			before(env);
			auto result = current_env->CallNonvirtualShortMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualIntMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jint {
			_INVOKE_DEBUG(CallNonvirtualIntMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jint result = current_env->CallNonvirtualIntMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualIntMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jint {
			_INVOKE_DEBUG(CallNonvirtualIntMethodV);
			before(env);
			auto result = current_env->CallNonvirtualIntMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualIntMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jint {
			_INVOKE_DEBUG(CallNonvirtualIntMethodA);
			before(env);
			auto result = current_env->CallNonvirtualIntMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualLongMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jlong {
			_INVOKE_DEBUG(CallNonvirtualLongMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jlong result = current_env->CallNonvirtualLongMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualLongMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jlong {
			_INVOKE_DEBUG(CallNonvirtualLongMethodV);
			before(env);
			auto result = current_env->CallNonvirtualLongMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualLongMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jlong {
			_INVOKE_DEBUG(CallNonvirtualLongMethodA);
			before(env);
			auto result = current_env->CallNonvirtualLongMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualFloatMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jfloat {
			_INVOKE_DEBUG(CallNonvirtualFloatMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jfloat result = current_env->CallNonvirtualFloatMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualFloatMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jfloat {
			_INVOKE_DEBUG(CallNonvirtualFloatMethodV);
			before(env);
			auto result = current_env->CallNonvirtualFloatMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualFloatMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jfloat {
			_INVOKE_DEBUG(CallNonvirtualFloatMethodA);
			before(env);
			auto result = current_env->CallNonvirtualFloatMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualDoubleMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) -> jdouble {
			_INVOKE_DEBUG(CallNonvirtualDoubleMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jdouble result = current_env->CallNonvirtualDoubleMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallNonvirtualDoubleMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) -> jdouble {
			_INVOKE_DEBUG(CallNonvirtualDoubleMethodV);
			before(env);
			auto result = current_env->CallNonvirtualDoubleMethodV(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualDoubleMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) -> jdouble {
			_INVOKE_DEBUG(CallNonvirtualDoubleMethodA);
			before(env);
			auto result = current_env->CallNonvirtualDoubleMethodA(obj, clazz, methodID, args);
			after(env);
			return result;
			};

		CallNonvirtualVoidMethod = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, ...) {
			_INVOKE_DEBUG(CallNonvirtualVoidMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			current_env->CallNonvirtualVoidMethodV(obj, clazz, methodID, args);
			va_end(args);
			after(env);
			};

		CallNonvirtualVoidMethodV = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, va_list args) {
			_INVOKE_DEBUG(CallNonvirtualVoidMethodV);
			before(env);
			current_env->CallNonvirtualVoidMethodV(obj, clazz, methodID, args);
			after(env);
			};

		CallNonvirtualVoidMethodA = [](JNIEnv* env, jobject obj, jclass clazz, jmethodID methodID, const jvalue* args) {
			_INVOKE_DEBUG(CallNonvirtualVoidMethodA);
			before(env);
			current_env->CallNonvirtualVoidMethodA(obj, clazz, methodID, args);
			after(env);
			};

		GetFieldID = [](JNIEnv* env, jclass clazz, const char* name, const char* sig) -> jfieldID {
			_INVOKE_DEBUG(GetFieldID);
			before(env);
			auto result = current_env->GetFieldID(clazz, name, sig);
			after(env);
			return result;
			};

		GetObjectField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jobject {
			_INVOKE_DEBUG(GetObjectField);
			before(env);
			auto result = current_env->GetObjectField(obj, fieldID);
			after(env);
			return result;
			};

		GetBooleanField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jboolean {
			_INVOKE_DEBUG(GetBooleanField);
			before(env);
			auto result = current_env->GetBooleanField(obj, fieldID);
			after(env);
			return result;
			};

		GetByteField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jbyte {
			_INVOKE_DEBUG(GetByteField);
			before(env);
			auto result = current_env->GetByteField(obj, fieldID);
			after(env);
			return result;
			};

		GetCharField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jchar {
			_INVOKE_DEBUG(GetCharField);
			before(env);
			auto result = current_env->GetCharField(obj, fieldID);
			after(env);
			return result;
			};

		GetShortField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jshort {
			_INVOKE_DEBUG(GetShortField);
			before(env);
			auto result = current_env->GetShortField(obj, fieldID);
			after(env);
			return result;
			};

		GetIntField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jint {
			_INVOKE_DEBUG(GetIntField);
			before(env);
			auto result = current_env->GetIntField(obj, fieldID);
			after(env);
			return result;
			};
		GetLongField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jlong {
			_INVOKE_DEBUG(GetLongField);
			before(env);
			auto result = current_env->GetLongField(obj, fieldID);
			after(env);
			return result;
			};

		GetFloatField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jfloat {
			_INVOKE_DEBUG(GetFloatField);
			before(env);
			auto result = current_env->GetFloatField(obj, fieldID);
			after(env);
			return result;
			};

		GetDoubleField = [](JNIEnv* env, jobject obj, jfieldID fieldID) -> jdouble {
			_INVOKE_DEBUG(GetDoubleField);
			before(env);
			auto result = current_env->GetDoubleField(obj, fieldID);
			after(env);
			return result;
			};

		SetObjectField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jobject val) {
			_INVOKE_DEBUG(SetObjectField);
			before(env);
			current_env->SetObjectField(obj, fieldID, val);
			after(env);
			};

		SetBooleanField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jboolean val) {
			_INVOKE_DEBUG(SetBooleanField);
			before(env);
			current_env->SetBooleanField(obj, fieldID, val);
			after(env);
			};

		SetByteField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jbyte val) {
			_INVOKE_DEBUG(SetByteField);
			before(env);
			current_env->SetByteField(obj, fieldID, val);
			after(env);
			};

		SetCharField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jchar val) {
			_INVOKE_DEBUG(SetCharField);
			before(env);
			current_env->SetCharField(obj, fieldID, val);
			after(env);
			};

		SetShortField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jshort val) {
			_INVOKE_DEBUG(SetShortField);
			before(env);
			current_env->SetShortField(obj, fieldID, val);
			after(env);
			};

		SetIntField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jint val) {
			_INVOKE_DEBUG(SetIntField);
			before(env);
			current_env->SetIntField(obj, fieldID, val);
			after(env);
			};

		SetLongField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jlong val) {
			_INVOKE_DEBUG(SetLongField);
			before(env);
			current_env->SetLongField(obj, fieldID, val);
			after(env);
			};

		SetFloatField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jfloat val) {
			_INVOKE_DEBUG(SetFloatField);
			before(env);
			current_env->SetFloatField(obj, fieldID, val);
			after(env);
			};

		SetDoubleField = [](JNIEnv* env, jobject obj, jfieldID fieldID, jdouble val) {
			_INVOKE_DEBUG(SetDoubleField);
			before(env);
			current_env->SetDoubleField(obj, fieldID, val);
			after(env);
			};


		GetStaticMethodID = [](JNIEnv* env, jclass clazz, const char* name, const char* sig) -> jmethodID {
#ifdef OUTPUT
			log << "DEBUG: JNINativeInterface_::" << "GetStaticMethodID name :" << name << " sig :" << sig << std::endl;
#endif // OUTPUT

			before(env);
			auto result = current_env->GetStaticMethodID(clazz, name, sig);
			after(env);
			return result;
			};


		CallStaticObjectMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jobject {
			_INVOKE_DEBUG(CallStaticObjectMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jobject result = current_env->CallStaticObjectMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticObjectMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jobject {
			_INVOKE_DEBUG(CallStaticObjectMethodV);
			before(env);
			auto result = current_env->CallStaticObjectMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticObjectMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jobject {
			_INVOKE_DEBUG(CallStaticObjectMethodA);
			before(env);
			auto result = current_env->CallStaticObjectMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticBooleanMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jboolean {
			_INVOKE_DEBUG(CallStaticBooleanMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jboolean result = current_env->CallStaticBooleanMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticBooleanMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jboolean {
			_INVOKE_DEBUG(CallStaticBooleanMethodV);
			before(env);
			auto result = current_env->CallStaticBooleanMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticBooleanMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jboolean {
			_INVOKE_DEBUG(CallStaticBooleanMethodA);
			before(env);
			auto result = current_env->CallStaticBooleanMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticByteMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jbyte {
			_INVOKE_DEBUG(CallStaticByteMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jbyte result = current_env->CallStaticByteMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticByteMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jbyte {
			_INVOKE_DEBUG(CallStaticByteMethodV);
			before(env);
			auto result = current_env->CallStaticByteMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticByteMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jbyte {
			_INVOKE_DEBUG(CallStaticByteMethodA);
			before(env);
			auto result = current_env->CallStaticByteMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticCharMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jchar {
			_INVOKE_DEBUG(CallStaticCharMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jchar result = current_env->CallStaticCharMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticCharMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jchar {
			_INVOKE_DEBUG(CallStaticCharMethodV);
			before(env);
			auto result = current_env->CallStaticCharMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticCharMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jchar {
			_INVOKE_DEBUG(CallStaticCharMethodA);
			before(env);
			auto result = current_env->CallStaticCharMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticShortMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jshort {
			_INVOKE_DEBUG(CallStaticShortMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jshort result = current_env->CallStaticShortMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticShortMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jshort {
			_INVOKE_DEBUG(CallStaticShortMethodV);
			before(env);
			auto result = current_env->CallStaticShortMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticShortMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jshort {
			_INVOKE_DEBUG(CallStaticShortMethodA);
			before(env);
			auto result = current_env->CallStaticShortMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticIntMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jint {
			_INVOKE_DEBUG(CallStaticIntMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jint result = current_env->CallStaticIntMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticIntMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jint {
			_INVOKE_DEBUG(CallStaticIntMethodV);
			before(env);
			auto result = current_env->CallStaticIntMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticIntMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jint {
			_INVOKE_DEBUG(CallStaticIntMethodA);
			before(env);
			auto result = current_env->CallStaticIntMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticLongMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jlong {
			_INVOKE_DEBUG(CallStaticLongMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jlong result = current_env->CallStaticLongMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticLongMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jlong {
			_INVOKE_DEBUG(CallStaticLongMethodV);
			before(env);
			auto result = current_env->CallStaticLongMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticLongMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jlong {
			_INVOKE_DEBUG(CallStaticLongMethodA);
			before(env);
			auto result = current_env->CallStaticLongMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticFloatMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jfloat {
			_INVOKE_DEBUG(CallStaticFloatMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jfloat result = current_env->CallStaticFloatMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticFloatMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jfloat {
			_INVOKE_DEBUG(CallStaticFloatMethodV);
			before(env);
			auto result = current_env->CallStaticFloatMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticFloatMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jfloat {
			_INVOKE_DEBUG(CallStaticFloatMethodA);
			before(env);
			auto result = current_env->CallStaticFloatMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticDoubleMethod = [](JNIEnv* env, jclass clazz, jmethodID methodID, ...) -> jdouble {
			_INVOKE_DEBUG(CallStaticDoubleMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			jdouble result = current_env->CallStaticDoubleMethodV(clazz, methodID, args);
			va_end(args);
			after(env);
			return result;
			};

		CallStaticDoubleMethodV = [](JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) -> jdouble {
			_INVOKE_DEBUG(CallStaticDoubleMethodV);
			before(env);
			auto result = current_env->CallStaticDoubleMethodV(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticDoubleMethodA = [](JNIEnv* env, jclass clazz, jmethodID methodID, const jvalue* args) -> jdouble {
			_INVOKE_DEBUG(CallStaticDoubleMethodA);
			before(env);
			auto result = current_env->CallStaticDoubleMethodA(clazz, methodID, args);
			after(env);
			return result;
			};

		CallStaticVoidMethod = [](JNIEnv* env, jclass cls, jmethodID methodID, ...) {
			_INVOKE_DEBUG(CallStaticVoidMethod);
			before(env);
			va_list args;
			va_start(args, methodID);
			current_env->CallStaticVoidMethodV(cls, methodID, args);
			va_end(args);
			after(env);
			};

		CallStaticVoidMethodV = [](JNIEnv* env, jclass cls, jmethodID methodID, va_list args) {
			_INVOKE_DEBUG(CallStaticVoidMethodV);
			before(env);
			current_env->CallStaticVoidMethodV(cls, methodID, args);
			after(env);
			};

		CallStaticVoidMethodA = [](JNIEnv* env, jclass cls, jmethodID methodID, const jvalue* args) {
			_INVOKE_DEBUG(CallStaticVoidMethodA);
			before(env);
			current_env->CallStaticVoidMethodA(cls, methodID, args);
			after(env);
			};

		GetStaticFieldID = [](JNIEnv* env, jclass clazz, const char* name, const char* sig) -> jfieldID {
			_INVOKE_DEBUG(GetStaticFieldID);
			before(env);
			auto result = current_env->GetStaticFieldID(clazz, name, sig);
			after(env);
			return result;
			};

		GetStaticObjectField = [](JNIEnv* env, jclass clazz, jfieldID fieldID) -> jobject {
			_INVOKE_DEBUG(GetStaticObjectField);
			before(env);
			auto result = current_env->GetStaticObjectField(clazz, fieldID);
			after(env);
			return result;
			};

		GetStaticBooleanField = [](JNIEnv* env, jclass clazz, jfieldID fieldID) -> jboolean {
			_INVOKE_DEBUG(GetStaticBooleanField);
			before(env);
			auto result = current_env->GetStaticBooleanField(clazz, fieldID);
			after(env);
			return result;
			};

		GetStaticByteField = [](JNIEnv* env, jclass clazz, jfieldID fieldID) -> jbyte {
			_INVOKE_DEBUG(GetStaticByteField);
			before(env);
			auto result = current_env->GetStaticByteField(clazz, fieldID);
			after(env);
			return result;
			};

		GetStaticShortField = [](JNIEnv* env, jclass clazz, jfieldID fieldID) -> jshort {
			_INVOKE_DEBUG(GetStaticShortField);
			before(env);
			auto result = current_env->GetStaticShortField(clazz, fieldID);
			after(env);
			return result;
			};

		GetStaticIntField = [](JNIEnv* env, jclass clazz, jfieldID fieldID) -> jint {
			_INVOKE_DEBUG(GetStaticIntField);
			before(env);
			auto result = current_env->GetStaticIntField(clazz, fieldID);
			after(env);
			return result;
			};

		GetStaticLongField = [](JNIEnv* env, jclass clazz, jfieldID fieldID) -> jlong {
			_INVOKE_DEBUG(GetStaticLongField);
			before(env);
			auto result = current_env->GetStaticLongField(clazz, fieldID);
			after(env);
			return result;
			};

		GetStaticFloatField = [](JNIEnv* env, jclass clazz, jfieldID fieldID) -> jfloat {
			_INVOKE_DEBUG(GetStaticFloatField);
			before(env);
			auto result = current_env->GetStaticFloatField(clazz, fieldID);
			after(env);
			return result;
			};

		GetStaticDoubleField = [](JNIEnv* env, jclass clazz, jfieldID fieldID) -> jdouble {
			_INVOKE_DEBUG(GetStaticDoubleField);
			before(env);
			auto result = current_env->GetStaticDoubleField(clazz, fieldID);
			after(env);
			return result;
			};

		SetStaticObjectField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jobject value) {
			_INVOKE_DEBUG(SetStaticObjectField);
			before(env);
			current_env->SetStaticObjectField(clazz, fieldID, value);
			after(env);
			};

		SetStaticBooleanField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jboolean value) {
			_INVOKE_DEBUG(SetStaticBooleanField);
			before(env);
			current_env->SetStaticBooleanField(clazz, fieldID, value);
			after(env);
			};

		SetStaticByteField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jbyte value) {
			_INVOKE_DEBUG(SetStaticByteField);
			before(env);
			current_env->SetStaticByteField(clazz, fieldID, value);
			after(env);
			};

		SetStaticCharField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jchar value) {
			_INVOKE_DEBUG(SetStaticCharField);
			before(env);
			current_env->SetStaticCharField(clazz, fieldID, value);
			after(env);
			};

		SetStaticShortField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jshort value) {
			_INVOKE_DEBUG(SetStaticShortField);
			before(env);
			current_env->SetStaticShortField(clazz, fieldID, value);
			after(env);
			};

		SetStaticIntField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jint value) {
			_INVOKE_DEBUG(SetStaticIntField);
			before(env);
			current_env->SetStaticIntField(clazz, fieldID, value);
			after(env);
			};

		SetStaticLongField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jlong value) {
			_INVOKE_DEBUG(SetStaticLongField);
			before(env);
			current_env->SetStaticLongField(clazz, fieldID, value);
			after(env);
			};

		SetStaticFloatField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jfloat value) {
			_INVOKE_DEBUG(SetStaticFloatField);
			before(env);
			current_env->SetStaticFloatField(clazz, fieldID, value);
			after(env);
			};

		SetStaticDoubleField = [](JNIEnv* env, jclass clazz, jfieldID fieldID, jdouble value) {
			_INVOKE_DEBUG(SetStaticDoubleField);
			before(env);
			current_env->SetStaticDoubleField(clazz, fieldID, value);
			after(env);
			};

		NewString = [](JNIEnv* env, const jchar* unicode, jsize len) -> jstring {
			_INVOKE_DEBUG(NewString);
			before(env);
			auto result = current_env->NewString(unicode, len);
			after(env);
			return result;
			};

		GetStringLength = [](JNIEnv* env, jstring str) -> jsize {
			_INVOKE_DEBUG(GetStringLength);
			before(env);
			auto result = current_env->GetStringLength(str);
			after(env);
			return result;
			};

		GetStringChars = [](JNIEnv* env, jstring str, jboolean* isCopy) -> const jchar* {
			_INVOKE_DEBUG(GetStringChars);
			before(env);
			auto result = current_env->GetStringChars(str, isCopy);
			after(env);
			return result;
			};

		ReleaseStringChars = [](JNIEnv* env, jstring str, const jchar* chars) {
			_INVOKE_DEBUG(ReleaseStringChars);
			before(env);
			current_env->ReleaseStringChars(str, chars);
			after(env);
			};

		NewStringUTF = [](JNIEnv* env, const char* utf) -> jstring {
#ifdef OUTPUT
			log << "DEBUG: JNINativeInterface_::" << "NewStringUTF : " << utf << std::endl;
#endif // OUTPUT

			before(env);
			auto result = current_env->functions->NewStringUTF(current_env, utf);
			after(env);
			return result;
			};

		GetStringUTFLength = [](JNIEnv* env, jstring str) -> jsize {
			_INVOKE_DEBUG(GetStringUTFLength);
			before(env);
			auto result = current_env->GetStringUTFLength(str);
			after(env);
			return result;
			};

		GetStringUTFChars = [](JNIEnv* env, jstring str, jboolean* isCopy) -> const char* {
			_INVOKE_DEBUG(GetStringUTFChars);
			before(env);
			auto result = current_env->GetStringUTFChars(str, isCopy);
			after(env);
			return result;
			};

		ReleaseStringUTFChars = [](JNIEnv* env, jstring str, const char* chars) {
			_INVOKE_DEBUG(ReleaseStringUTFChars);
			before(env);
			current_env->ReleaseStringUTFChars(str, chars);
			after(env);
			};

		GetArrayLength = [](JNIEnv* env, jarray array) -> jsize {
			_INVOKE_DEBUG(GetArrayLength);
			before(env);
			auto result = current_env->GetArrayLength(array);
			after(env);
			return result;
			};

		NewObjectArray = [](JNIEnv* env, jsize len, jclass clazz, jobject init) -> jobjectArray {
			_INVOKE_DEBUG(NewObjectArray);
			before(env);
			auto result = current_env->NewObjectArray(len, clazz, init);
			after(env);
			return result;
			};

		GetObjectArrayElement = [](JNIEnv* env, jobjectArray array, jsize index) -> jobject {
			_INVOKE_DEBUG(GetObjectArrayElement);
			before(env);
			auto result = current_env->GetObjectArrayElement(array, index);
			after(env);
			return result;
			};

		SetObjectArrayElement = [](JNIEnv* env, jobjectArray array, jsize index, jobject val) {
			_INVOKE_DEBUG(SetObjectArrayElement);
			before(env);
			current_env->SetObjectArrayElement(array, index, val);
			after(env);
			};

		NewBooleanArray = [](JNIEnv* env, jsize len) -> jbooleanArray {
			_INVOKE_DEBUG(NewBooleanArray);
			before(env);
			auto result = current_env->NewBooleanArray(len);
			after(env);
			return result;
			};

		NewByteArray = [](JNIEnv* env, jsize len) -> jbyteArray {
			_INVOKE_DEBUG(NewByteArray);
			before(env);
			auto result = current_env->NewByteArray(len);
			after(env);
			return result;
			};

		NewCharArray = [](JNIEnv* env, jsize len) -> jcharArray {
			_INVOKE_DEBUG(NewCharArray);
			before(env);
			auto result = current_env->NewCharArray(len);
			after(env);
			return result;
			};

		NewShortArray = [](JNIEnv* env, jsize len) -> jshortArray {
			_INVOKE_DEBUG(NewShortArray);
			before(env);
			auto result = current_env->NewShortArray(len);
			after(env);
			return result;
			};

		NewIntArray = [](JNIEnv* env, jsize len) -> jintArray {
			_INVOKE_DEBUG(NewIntArray);
			before(env);
			auto result = current_env->NewIntArray(len);
			after(env);
			return result;
			};

		NewLongArray = [](JNIEnv* env, jsize len) -> jlongArray {
			_INVOKE_DEBUG(NewLongArray);
			before(env);
			auto result = current_env->NewLongArray(len);
			after(env);
			return result;
			};

		NewFloatArray = [](JNIEnv* env, jsize len) -> jfloatArray {
			_INVOKE_DEBUG(NewFloatArray);
			before(env);
			auto result = current_env->NewFloatArray(len);
			after(env);
			return result;
			};

		NewDoubleArray = [](JNIEnv* env, jsize len) -> jdoubleArray {
			_INVOKE_DEBUG(NewDoubleArray);
			before(env);
			auto result = current_env->NewDoubleArray(len);
			after(env);
			return result;
			};

		GetBooleanArrayElements = [](JNIEnv* env, jbooleanArray array, jboolean* isCopy) -> jboolean* {
			_INVOKE_DEBUG(GetBooleanArrayElements);
			before(env);
			auto result = current_env->GetBooleanArrayElements(array, isCopy);
			after(env);
			return result;
			};

		GetByteArrayElements = [](JNIEnv* env, jbyteArray array, jboolean* isCopy) -> jbyte* {
			_INVOKE_DEBUG(GetByteArrayElements);
			before(env);
			auto result = current_env->GetByteArrayElements(array, isCopy);
			after(env);
			return result;
			};

		GetCharArrayElements = [](JNIEnv* env, jcharArray array, jboolean* isCopy) -> jchar* {
			_INVOKE_DEBUG(GetCharArrayElements);
			before(env);
			auto result = current_env->GetCharArrayElements(array, isCopy);
			after(env);
			return result;
			};

		GetShortArrayElements = [](JNIEnv* env, jshortArray array, jboolean* isCopy) -> jshort* {
			_INVOKE_DEBUG(GetShortArrayElements);
			before(env);
			auto result = current_env->GetShortArrayElements(array, isCopy);
			after(env);
			return result;
			};

		GetIntArrayElements = [](JNIEnv* env, jintArray array, jboolean* isCopy) -> jint* {
			_INVOKE_DEBUG(GetIntArrayElements);
			before(env);
			auto result = current_env->GetIntArrayElements(array, isCopy);
			after(env);
			return result;
			};

		GetLongArrayElements = [](JNIEnv* env, jlongArray array, jboolean* isCopy) -> jlong* {
			_INVOKE_DEBUG(GetLongArrayElements);
			before(env);
			auto result = current_env->GetLongArrayElements(array, isCopy);
			after(env);
			return result;
			};

		GetFloatArrayElements = [](JNIEnv* env, jfloatArray array, jboolean* isCopy) -> jfloat* {
			_INVOKE_DEBUG(GetFloatArrayElements);
			before(env);
			auto result = current_env->GetFloatArrayElements(array, isCopy);
			after(env);
			return result;
			};

		GetDoubleArrayElements = [](JNIEnv* env, jdoubleArray array, jboolean* isCopy) -> jdouble* {
			_INVOKE_DEBUG(GetDoubleArrayElements);
			before(env);
			auto result = current_env->GetDoubleArrayElements(array, isCopy);
			after(env);
			return result;
			};

		ReleaseBooleanArrayElements = [](JNIEnv* env, jbooleanArray array, jboolean* elems, jint mode) {
			_INVOKE_DEBUG(ReleaseBooleanArrayElements);
			before(env);
			current_env->ReleaseBooleanArrayElements(array, elems, mode);
			after(env);
			};

		ReleaseByteArrayElements = [](JNIEnv* env, jbyteArray array, jbyte* elems, jint mode) {
			_INVOKE_DEBUG(ReleaseByteArrayElements);
			before(env);
			current_env->ReleaseByteArrayElements(array, elems, mode);
			after(env);
			};

		ReleaseCharArrayElements = [](JNIEnv* env, jcharArray array, jchar* elems, jint mode) {
			_INVOKE_DEBUG(ReleaseCharArrayElements);
			before(env);
			current_env->ReleaseCharArrayElements(array, elems, mode);
			after(env);
			};

		ReleaseShortArrayElements = [](JNIEnv* env, jshortArray array, jshort* elems, jint mode) {
			_INVOKE_DEBUG(ReleaseShortArrayElements);
			before(env);
			current_env->ReleaseShortArrayElements(array, elems, mode);
			after(env);
			};

		ReleaseIntArrayElements = [](JNIEnv* env, jintArray array, jint* elems, jint mode) {
			_INVOKE_DEBUG(ReleaseIntArrayElements);
			before(env);
			current_env->ReleaseIntArrayElements(array, elems, mode);
			after(env);
			};

		ReleaseLongArrayElements = [](JNIEnv* env, jlongArray array, jlong* elems, jint mode) {
			_INVOKE_DEBUG(ReleaseLongArrayElements);
			before(env);
			current_env->ReleaseLongArrayElements(array, elems, mode);
			after(env);
			};

		ReleaseFloatArrayElements = [](JNIEnv* env, jfloatArray array, jfloat* elems, jint mode) {
			_INVOKE_DEBUG(ReleaseFloatArrayElements);
			before(env);
			current_env->ReleaseFloatArrayElements(array, elems, mode);
			after(env);
			};

		ReleaseDoubleArrayElements = [](JNIEnv* env, jdoubleArray array, jdouble* elems, jint mode) {
			_INVOKE_DEBUG(ReleaseDoubleArrayElements);
			before(env);
			current_env->ReleaseDoubleArrayElements(array, elems, mode);
			after(env);
			};

		GetBooleanArrayRegion = [](JNIEnv* env, jbooleanArray array, jsize start, jsize l, jboolean* buf) {
			_INVOKE_DEBUG(GetBooleanArrayRegion);
			before(env);
			current_env->GetBooleanArrayRegion(array, start, l, buf);
			after(env);
			};

		GetByteArrayRegion = [](JNIEnv* env, jbyteArray array, jsize start, jsize len, jbyte* buf) {
			_INVOKE_DEBUG(GetByteArrayRegion);
			before(env);
			current_env->GetByteArrayRegion(array, start, len, buf);
			after(env);
			};

		GetCharArrayRegion = [](JNIEnv* env, jcharArray array, jsize start, jsize len, jchar* buf) {
			_INVOKE_DEBUG(GetCharArrayRegion);
			before(env);
			current_env->GetCharArrayRegion(array, start, len, buf);
			after(env);
			};

		GetShortArrayRegion = [](JNIEnv* env, jshortArray array, jsize start, jsize len, jshort* buf) {
			_INVOKE_DEBUG(GetShortArrayRegion);
			before(env);
			current_env->GetShortArrayRegion(array, start, len, buf);
			after(env);
			};

		GetIntArrayRegion = [](JNIEnv* env, jintArray array, jsize start, jsize len, jint* buf) {
			_INVOKE_DEBUG(GetIntArrayRegion);
			before(env);
			current_env->GetIntArrayRegion(array, start, len, buf);
			after(env);
			};

		GetLongArrayRegion = [](JNIEnv* env, jlongArray array, jsize start, jsize len, jlong* buf) {
			_INVOKE_DEBUG(GetLongArrayRegion);
			before(env);
			current_env->GetLongArrayRegion(array, start, len, buf);
			after(env);
			};

		GetFloatArrayRegion = [](JNIEnv* env, jfloatArray array, jsize start, jsize len, jfloat* buf) {
			_INVOKE_DEBUG(GetFloatArrayRegion);
			before(env);
			current_env->GetFloatArrayRegion(array, start, len, buf);
			after(env);
			};
		GetDoubleArrayRegion = [](JNIEnv* env, jdoubleArray array, jsize start, jsize len, jdouble* buf) {
			_INVOKE_DEBUG(GetDoubleArrayRegion);
			before(env);
			current_env->GetDoubleArrayRegion(array, start, len, buf);
			after(env);
			};

		SetBooleanArrayRegion = [](JNIEnv* env, jbooleanArray array, jsize start, jsize l, const jboolean* buf) {
			_INVOKE_DEBUG(SetBooleanArrayRegion);
			before(env);
			current_env->SetBooleanArrayRegion(array, start, l, buf);
			after(env);
			};

		SetByteArrayRegion = [](JNIEnv* env, jbyteArray array, jsize start, jsize len, const jbyte* buf) {
			_INVOKE_DEBUG(SetByteArrayRegion);
			before(env);
			current_env->SetByteArrayRegion(array, start, len, buf);
			after(env);
			};

		SetCharArrayRegion = [](JNIEnv* env, jcharArray array, jsize start, jsize len, const jchar* buf) {
			_INVOKE_DEBUG(SetCharArrayRegion);
			before(env);
			current_env->SetCharArrayRegion(array, start, len, buf);
			after(env);
			};

		SetShortArrayRegion = [](JNIEnv* env, jshortArray array, jsize start, jsize len, const jshort* buf) {
			_INVOKE_DEBUG(SetShortArrayRegion);
			before(env);
			current_env->SetShortArrayRegion(array, start, len, buf);
			after(env);
			};

		SetIntArrayRegion = [](JNIEnv* env, jintArray array, jsize start, jsize len, const jint* buf) {
			_INVOKE_DEBUG(SetIntArrayRegion);
			before(env);
			current_env->SetIntArrayRegion(array, start, len, buf);
			after(env);
			};

		SetLongArrayRegion = [](JNIEnv* env, jlongArray array, jsize start, jsize len, const jlong* buf) {
			_INVOKE_DEBUG(SetLongArrayRegion);
			before(env);
			current_env->SetLongArrayRegion(array, start, len, buf);
			after(env);
			};

		SetFloatArrayRegion = [](JNIEnv* env, jfloatArray array, jsize start, jsize len, const jfloat* buf) {
			_INVOKE_DEBUG(SetFloatArrayRegion);
			before(env);
			current_env->SetFloatArrayRegion(array, start, len, buf);
			after(env);
			};

		SetDoubleArrayRegion = [](JNIEnv* env, jdoubleArray array, jsize start, jsize len, const jdouble* buf) {
			_INVOKE_DEBUG(SetDoubleArrayRegion);
			before(env);
			current_env->SetDoubleArrayRegion(array, start, len, buf);
			after(env);
			};

		RegisterNatives = [](JNIEnv* env, jclass clazz, const JNINativeMethod* methods, jint nMethods) -> jint {
			static int count = 0;
			_INVOKE_DEBUG(RegisterNatives);
			for (size_t i = 0; i < nMethods; i++)
			{
				const auto& method = methods[i];
				HMODULE hModule;

				char* clazzSign{};
				current_context->jvmti.value()->GetClassSignature(clazz, &clazzSign, 0);
				std::string class_name(clazzSign);

				utils::misc::to_java_class_name(class_name);

				if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)method.fnPtr, &hModule)) {
					auto offset = (uintptr_t)method.fnPtr - (uintptr_t)hModule;
					count++;
					auto cmp_class_name_src = "if (class_name == \"" + class_name + "\"" + "){";
					//auto find_class_src = "auto clazz_" + std::to_string(count) + " = env->FindClass(\"" + class_name + "\");";
					auto native_methods_var_name = "\tnativeMethods_" + std::to_string(count);
					auto native_methods_src = "\tconst JNINativeMethod " + native_methods_var_name + "[] = { \n{const_cast<char*>(\"" + method.name + "\" , const_cast<char*>(\"" + method.signature + "\") , reinterpret_cast<void*>(module_base + " + std::to_string(offset) + ") } \n};";
					auto register_src = "\tenv->RegisterNatives(clazz, " + native_methods_var_name + ", 1);";
					std::ofstream outfile("output.txt", std::ios::app);
					outfile << cmp_class_name_src << "\n" << native_methods_src << "\n" << register_src << "\n}" << std::endl;
					outfile.close();
				}
				else {
					log << "Failed GetModuleHandleEx" << std::endl;
				}

			}
			before(env);
			auto result = current_env->RegisterNatives(clazz, methods, nMethods);
			after(env);
			return result;
			};

		UnregisterNatives = [](JNIEnv* env, jclass clazz) -> jint {
			_INVOKE_DEBUG(UnregisterNatives);
			before(env);
			auto result = current_env->UnregisterNatives(clazz);
			after(env);
			return result;
			};

		MonitorEnter = [](JNIEnv* env, jobject obj) -> jint {
			_INVOKE_DEBUG(MonitorEnter);
			before(env);
			auto result = current_env->MonitorEnter(obj);
			after(env);
			return result;
			};

		MonitorExit = [](JNIEnv* env, jobject obj) -> jint {
			_INVOKE_DEBUG(MonitorExit);
			before(env);
			auto result = current_env->MonitorExit(obj);
			after(env);
			return result;
			};

		GetJavaVM = [](JNIEnv* env, JavaVM** vm) -> jint {
			_INVOKE_DEBUG(GetJavaVM);
			before(env);
			auto result = current_env->GetJavaVM(vm);
			after(env);
			return result;
			};

		GetStringRegion = [](JNIEnv* env, jstring str, jsize start, jsize len, jchar* buf) {
			_INVOKE_DEBUG(GetStringRegion);
			before(env);
			current_env->GetStringRegion(str, start, len, buf);
			after(env);
			};

		GetStringUTFRegion = [](JNIEnv* env, jstring str, jsize start, jsize len, char* buf) {
			_INVOKE_DEBUG(GetStringUTFRegion);
			before(env);
			current_env->GetStringUTFRegion(str, start, len, buf);
			after(env);
			};

		GetPrimitiveArrayCritical = [](JNIEnv* env, jarray array, jboolean* isCopy) -> void* {
			_INVOKE_DEBUG(GetPrimitiveArrayCritical);
			before(env);
			auto result = current_env->GetPrimitiveArrayCritical(array, isCopy);
			after(env);
			return result;
			};

		ReleasePrimitiveArrayCritical = [](JNIEnv* env, jarray array, void* carray, jint mode) {
			_INVOKE_DEBUG(ReleasePrimitiveArrayCritical);
			before(env);
			current_env->ReleasePrimitiveArrayCritical(array, carray, mode);
			after(env);
			};

		GetStringCritical = [](JNIEnv* env, jstring string, jboolean* isCopy) -> const jchar* {
			_INVOKE_DEBUG(GetStringCritical);
			before(env);
			auto result = current_env->GetStringCritical(string, isCopy);
			after(env);
			return result;
			};

		ReleaseStringCritical = [](JNIEnv* env, jstring string, const jchar* cstring) {
			_INVOKE_DEBUG(ReleaseStringCritical);
			before(env);
			current_env->ReleaseStringCritical(string, cstring);
			after(env);
			};

		NewWeakGlobalRef = [](JNIEnv* env, jobject obj) -> jweak {
			_INVOKE_DEBUG(NewWeakGlobalRef);
			before(env);
			auto result = current_env->NewWeakGlobalRef(obj);
			after(env);
			return result;
			};

		DeleteWeakGlobalRef = [](JNIEnv* env, jweak ref) {
			_INVOKE_DEBUG(DeleteWeakGlobalRef);
			before(env);
			current_env->DeleteWeakGlobalRef(ref);
			after(env);
			};

		ExceptionCheck = [](JNIEnv* env) -> jboolean {
			_INVOKE_DEBUG(ExceptionCheck);
			before(env);
			auto result = current_env->ExceptionCheck();
			after(env);
			return result;
			};

		NewDirectByteBuffer = [](JNIEnv* env, void* address, jlong capacity) -> jobject {
			_INVOKE_DEBUG(NewDirectByteBuffer);
			before(env);
			auto result = current_env->NewDirectByteBuffer(address, capacity);
			after(env);
			return result;
			};

		GetDirectBufferAddress = [](JNIEnv* env, jobject buf) -> void* {
			_INVOKE_DEBUG(GetDirectBufferAddress);
			before(env);
			auto result = current_env->GetDirectBufferAddress(buf);
			after(env);
			return result;
			};

		GetDirectBufferCapacity = [](JNIEnv* env, jobject buf) -> jlong {
			_INVOKE_DEBUG(GetDirectBufferCapacity);
			before(env);
			auto result = current_env->GetDirectBufferCapacity(buf);
			after(env);
			return result;
			};

		GetObjectRefType = [](JNIEnv* env, jobject obj) -> jobjectRefType {
			_INVOKE_DEBUG(GetObjectRefType);
			before(env);
			auto result = current_env->GetObjectRefType(obj);
			after(env);
			return result;
			};
	}
};



struct FakeJNIEnv : public JNIEnv_
{
	FakeJNIEnv() {
		this->functions = new FakeNativeInterface();
	}
};

END_FAKE_NAMESPACE

