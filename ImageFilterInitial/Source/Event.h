#pragma once

#include <functional>

template<typename... Args>
using Event = std::function<void(Args...)>;
