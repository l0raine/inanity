#ifndef ___INANITY_CONFIG_HPP___
#define ___INANITY_CONFIG_HPP___

/*
 * Конфигурация Inanity для компиляции.
 */

#if defined(_WIN32) || defined(__WIN32__)
#define ___INANITY_WINDOWS
#else
#define ___INANITY_LINUX
#endif

#ifdef ___INANITY_WINDOWS
// чтобы не объявлялись макросы MIN и MAX
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif // ___INANITY_WINDOWS

#ifdef ___INANITY_LINUX
#define DebugBreak() asm("int3")
#endif // ___INANITY_LINUX

#define BEGIN_INANITY namespace Inanity {
#define END_INANITY }

#ifdef INANITY_LIB

BEGIN_INANITY
END_INANITY
using namespace Inanity;

#endif

#endif
