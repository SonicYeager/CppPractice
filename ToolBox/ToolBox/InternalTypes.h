#pragma once
#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include <functional>
#include <future>
#include <iostream>
#include <sstream>
#include <experimental/coroutine>
#include <iterator>
#include <utility>
#include <concepts>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "Concepts.h"

namespace TOOLBOX
{
	class Dummy
	{
	public:
		int i = 1234;
		double z = 3489.34;
		std::string text = "some text to discuss";
	};

	template <typename T>
	using is_iterable = decltype(is_iterable_impl<T>(0));
	using Path = std::filesystem::path;
	using Lines = std::vector<std::string>;
}