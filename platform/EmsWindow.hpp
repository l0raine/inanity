#ifndef ___INANITY_PLATFORM_EMS_WINDOW_HPP___
#define ___INANITY_PLATFORM_EMS_WINDOW_HPP___

#include "Window.hpp"
#include "../input/input.hpp"

#ifndef ___INANITY_PLATFORM_EMSCRIPTEN
#error EmsWindow is for Emscripten platform
#endif

BEGIN_INANITY_INPUT

class Manager;

END_INANITY_INPUT

BEGIN_INANITY_PLATFORM

class Sdl;

/// Dummy window class for Emscripten platform.
class EmsWindow : public Window
{
private:
	ptr<Sdl> sdl;
	String title;
	ptr<Handler> activeHandler;
	ptr<Input::Manager> inputManager;

	/// Emscripten window can be only one.
	static EmsWindow* instance;

	/// Callback to emscripten to execute as a main loop.
	static void MainLoop();

	void UpdateMouseLock();
	void UpdateCursorVisible();

public:
	EmsWindow(const String& title, int width, int height);
	~EmsWindow();

	void SetInputManager(ptr<Input::Manager> inputManager);

	//*** Window's methods.
	void SetTitle(const String& title);
	void Close();
	void Run(ptr<Handler> activeHandler);
	ptr<Graphics::Output> CreateOutput();
	void PlaceCursor(int x, int y);
};

END_INANITY_PLATFORM

#endif
