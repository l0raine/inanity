#ifndef ___INANITY_GUI_TYPES_HPP___
#define ___INANITY_GUI_TYPES_HPP___

#include "gui.hpp"
#include "../inanity-math.hpp"

BEGIN_INANITY_GUI

/// Тип, используемый для указания позиции.
typedef float2 Position;
/// Тип, используемый для указания размера.
typedef float2 Size;

/// Кнопки мыши.
enum MouseButton
{
	Left, Right, Middle
};

/// Тип для клавиш клавиатуры.
typedef unsigned int Key;

END_INANITY_GUI

#endif