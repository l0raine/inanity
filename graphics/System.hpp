#ifndef ___INANITY_GRAPHICS_SYSTEM_HPP___
#define ___INANITY_GRAPHICS_SYSTEM_HPP___

#include "graphics.hpp"

#ifdef ___INANITY_GRAPHICS_DX

#include "dx/System.hpp"
BEGIN_INANITY_GRAPHICS
typedef DX::System System;
END_INANITY_GRAPHICS

#endif

#endif