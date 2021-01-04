#pragma once

#define STD_API_PRIORITY 2
#ifndef KISHI_API
#define KISHI_API STD_API_PRIORITY

#include <vector>

template<typename T>
using KArray=std::vector<T>;
#endif