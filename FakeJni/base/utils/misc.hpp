#pragma once
#include <iostream>
#include <type_traits>
#include <concepts>
#include "str.hpp"
namespace utils {
	namespace misc {
		inline std::string& to_java_class_name(std::string& class_name) {

			utils::strutil::replace_all(class_name, "\\", ".");
			utils::strutil::replace_all(class_name, "/", ".");
			class_name.erase(class_name.begin());
			class_name.pop_back();
			return class_name;
		}
		template<std::equality_comparable T, typename... Values, typename = std::enable_if_t<(std::equality_comparable_with<T, Values> && ...)>>
		inline bool is_any_of(T val, Values... values)
		{
			return ((val == values) || ...);
		}
	}
}