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

#ifdef TOOLBOXDLL_EXPORTS
#define TOOLBOX_API __declspec(dllexport)
#else
#define TOOLBOX_API __declspec(dllimport)
#endif

namespace TOOLBOX
{
	using Path = std::filesystem::path;
	using Lines = std::vector<std::string>;
}