# CMakeList.txt: CMake-Projekt für "CMakeTesty". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.19)

project ("CMakeTesty" VERSION 0.1)
configure_file(Config.h.in Config.h)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (CMakeTesty "CMakeTesty.cpp" "CMakeTesty.h")

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.

target_include_directories("CMakeTesty" PUBLIC
						   "${PROJECT_BINARY_DIR}"
						   )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)