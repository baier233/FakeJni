#pragma once

#include <jni/jni.h>
#include <jni/jvmti.h>
#include <jni/jvmti.h>

#include <iostream>
#include <functional>
#include <optional>
#include <format>
#include <fstream>

#include "utils/misc.hpp"
#include "utils/str.hpp"


#define BEGIN_FAKE_NAMESPACE namespace FakeJNI{

#define END_FAKE_NAMESPACE }