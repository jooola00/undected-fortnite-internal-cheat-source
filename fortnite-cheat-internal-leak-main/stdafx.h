#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define E(str) _xor_(str).c_str()
#define skCrypt(str) _xor_(str).c_str()
#include <stdio.h>
#include <Windows.h>
#include <psapi.h>
#include <intrin.h>

#include <string>
#include <vector>

#pragma intrinsic(_ReturnAddress)

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <map>

static const void* SPuuf;

using namespace std;

#define M_PI	3.14159265358979323846264338327950288419716939937510

// Auto Padding
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset)
