#ifndef CMD_PCH_H
#define CMD_PCH_H

// --<standard>--
// --stl
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <functional>
#include <algorithm>
// --streams
//#include <iomanip>
//#include <streambuf>
#include <iostream>
//#include <ostream>
//#include <istream>
#include <sstream>
#include <fstream>
//#include <iosfwd>
//#include <ios>
// --numbers
#include <random>
//#include <complex>
//#include <valarray>
//#include <numeric>
//#include <limits>
// --strings
#include <string>
//#include <regex>
// --support
#include <exception>
//#include <stdexcept>
//#include <locale>
#include <typeinfo>
#include <typeindex>
// --memory
#include <new>
#include <memory>
// --parallel computation
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
// --</standard>--

// --<native>--
#include <cstddef>

#include <cstdarg>
#include <cstdio>
#include <conio.h>
#include <ctime>

//#include <cassert>
//#include <clocale>
//#include <climits>
//#include <cerrno>

//#include <cfloat>
//#include <cmath>

//#include <cstring>
//#include <cctype>
//#include <cwchar>
//#include <cwctype>
// --</native>--

// --<platform>--
#ifdef CMD_PLATFORM_WINDOWS
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#endif	// CMD_PLATFORM
// --</platform>--

#endif // CMD_PCH_H