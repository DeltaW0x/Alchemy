//
// Created by lucac on 27/05/2024.
//

#ifndef STDAFX_H
#define STDAFX_H

#ifdef WIN32
#include <windows.h>
#undef min
#undef max
#endif

#ifdef _DEBUG
constexpr bool g_bDebug = true;
#else
constexpr bool g_bDebug = false;
#endif
#include <flecs.h>
#include <ostream>
#include <iostream>
#include <SDL3/SDL.h>
#include "../Miscellaneous/Types.h"

















#include <DirectXMath.h> // THIS SHOULD ALWAYS BE INCLUDED LAST
#endif //STDAFX_H
