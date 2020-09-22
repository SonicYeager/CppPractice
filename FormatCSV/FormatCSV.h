#pragma once
#include <vector>
#include <string>

#ifdef FORMATCSV_EXPORT
#define FORMATCSV_API __declspec(dllexport)
#else
#define FORMATCSV_API __declspec(dllimport)
#endif

//using Lines = std::vector<std::string>;

FORMATCSV_API std::vector<std::string> TabulateCSV(const std::vector<std::string>&);