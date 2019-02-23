#pragma once

#ifdef _WIN32
#include "windows/server_windows.h"
#else
#include "linux/server_linux.h"
#endif