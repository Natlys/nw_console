#ifndef CMD_PCH_H
#define CMD_PCH_H

// --<standard>--
// --stl
#include <utility>
#include <functional>
#include <algorithm>
// --</standard>--

// --<native>--
#include <cstddef>

#include <cstdarg>
#include <cstdio>
#include <conio.h>
#include <ctime>
// --</native>--

// --<platform>--
#ifdef CMD_PLATFORM_WINDOWS
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#endif	// CMD_PLATFORM
// --</platform>--

#include <native_world_library.hpp>

#endif // CMD_PCH_H