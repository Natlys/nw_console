#ifndef CMD_PCH_HPP
#define CMD_PCH_HPP

// --<standard>--
// --stl
#include <utility>
#include <functional>
#include <algorithm>
// --support
#include <exception>
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
using namespace NWL;

#endif // CMD_PCH_HPP