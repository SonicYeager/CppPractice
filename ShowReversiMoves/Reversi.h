#pragma once
#include <array>

using Board = std::array<std::array<char, 8>, 8>;

Board ShowNextMoves(const Board&, char);